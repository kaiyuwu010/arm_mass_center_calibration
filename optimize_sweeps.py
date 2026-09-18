#!/usr/bin/env python3
import argparse
import copy
from pathlib import Path
import numpy as np
import yaml

from calibrate_links import gravity_vector, load_config, regressor, validate_plan

ROOT = Path(__file__).resolve().parent
SCALE = np.tile([1., .1, .1, .1], 7)

# 统计足够大的奇异值数量，也就是秩
def rank(singular):
    # 必须大于1e-10，或最大奇异值singular[0]的万分之一
    return int(np.sum(singular > max(1e-10, singular[0]*1e-4))) if len(singular) else 0

# 构建回归矩阵，返回的矩阵形状是sweeps.size() X points.size() X 28
def matrix(sweeps, cfg, gravity):
    rows = []
    # 遍历扫描
    for sweep in sweeps:
        j = sweep['joint'] - 1
        # 遍历当前扫描的数据点
        for point in sweep['points_deg']:
            q = np.array(sweep['pose_deg'], dtype=float)
            q[j] = point
            # 这里只取了regressor返回的7X28矩阵中第j行
            rows.append(regressor(q, cfg, gravity)[j]*SCALE)
    return np.asarray(rows)

# 评价输入的扫描数据
def metrics(A, basis):
    singular = np.linalg.svd(A @ basis, compute_uv=False)
    r = rank(singular)
    return dict(rank=r,                                                                         # 扫描实际覆盖的有效方向数量
                target_rank=basis.shape[1],                                                     # 希望覆盖的方向总数
                min_singular=float(singular[-1]) if len(singular) >= basis.shape[1] else 0.,    # 最小奇异值
                condition=float(singular[0]/singular[-1]) if r == basis.shape[1] else None)     # 最大最小奇异值的比

def optimize(cfg, plan, gravity, lower, upper, count, candidates, seed):
    rng = np.random.default_rng(seed)
    # 在给定空间随机生成256组关节姿态，计算每组姿态的归一化矩阵，按行拼接，形状1792X28
    reference = np.vstack([regressor(q, cfg, gravity)*SCALE for q in rng.uniform(lower, upper, (256, 7))])
    _, singular, vt = np.linalg.svd(reference, full_matrices=False)
    # 计算矩阵的秩
    r = rank(singular)
    print(f"矩阵的秩为: {r}")
    if not r:
        raise ValueError('给定姿态范围没有可辨识的重力参数!!!')
    # 根据秩取出vt的前r行，转置后形状为: 28Xr
    basis = vt[:r].T
    check = np.vstack([regressor(q, cfg, gravity)*SCALE for q in rng.uniform(lower, upper, (128, 7))])
    # 先把check投影到basis，再用basis.T还原，如果还原后的矩阵与原来的差不多，投影损失residual会很小
    projection_error = np.linalg.norm(check - (check @ basis) @ basis.T)
    check_norm = np.linalg.norm(check)
    residual = projection_error/check_norm
    print(f"投影误差范数: {projection_error:.16g}")
    print(f"check范数: {check_norm:.16g}")
    print(f"残差为: {residual:.16g}")
    # 根据投影损失的大小和测试矩阵svd分解后的秩，判断秩是否可靠
    if residual > 1e-6 or rank(np.linalg.svd(check, compute_uv = False)) != r:
        raise ValueError('随机生成的参考子空间不稳定，请扩大姿态范围后重试!!!')
    # 保留原有候选，并复用各轴的扫描范围/采样点，每次扫描只有一个轴运动
    pool = copy.deepcopy(plan['sweeps'])
    templates = {}
    # 遍历扫描
    for sweep in pool:
        # 把扫描的关节id、关节运动范围、关节采样点合并作为字典templates的键
        key = (sweep['joint'], tuple(sweep['range_deg']), tuple(sweep['points_deg']))
        # 不同的关节位置覆盖同一个键
        templates[key] = sweep
    # 遍历模板
    for template in templates.values():
        # 在各关节限位内生成随机姿态，共candidates行7列，遍历每行
        for q in rng.uniform(lower, upper, (candidates, 7)):
            sweep = copy.deepcopy(template)
            # 将随机关节角度限制在范围内，np.nextafter(a, b)表示从浮点数a向b的方向走一点
            sweep['pose_deg'] = np.clip(np.round(q, 3), np.nextafter(lower, upper), np.nextafter(upper, lower)).tolist()
            # 将新增的扫描加入候选池
            pool.append(sweep)
    unique = {}
    # 遍历pool的每个扫描
    for sweep in pool:
        # 将扫描轴的基准角度设置为运动范围的中点
        sweep['pose_deg'][sweep['joint']-1] = sum(sweep['range_deg'])/2
        # 构造包含完整扫描信息的键
        key = (sweep['joint'], tuple(sweep['pose_deg']), tuple(sweep['range_deg']), tuple(sweep['points_deg']))
        unique[key] = sweep
    # 重新赋值给pool
    pool = list(unique.values())
    validate_plan(dict(plan, sweeps=pool), cfg)
    # 从pool里取出轨迹构建回归矩阵的行，投影到basis，blocks的形状是: 扫描数 X (每条扫描采样数 X r)
    blocks = [matrix([s], cfg, gravity) @ basis for s in pool]
    # 检查候选扫描的秩是否小于r
    if rank(np.linalg.svd(np.vstack(blocks), compute_uv=False)) < r:
        raise ValueError('候选扫描不能覆盖目标秩，请增加候选数量、姿态范围或扫描轴!!!')
    if count > len(pool):
        raise ValueError('扫描数量超过不重复候选数量!!!')
    # 构造信息矩阵，b的形状是: (每条扫描采样点数, r)，grams的形状是: (扫描数, r, r)
    grams = np.array([b.T @ b for b in blocks])
    # 先从扫描数个(r, r)信息矩阵生成迹，再从中取最大值，最大值再缩小1e-8，不能小于1e-12
    ridge = max(float(np.max(np.trace(grams, axis1 = 1, axis2=2)))*1e-8, 1e-12)
    info = np.zeros((r, r))
    available = np.ones(len(pool), dtype=bool) # 记录扫描是否已经被选择
    chosen = []
    # 每次从剩余候选中选出一条最有用的扫描，先看秩，再看信息量评分
    for _ in range(count):
        # 取出available中所有True元素的下标
        ids = np.flatnonzero(available)
        # grams[ids]表示剩余候选的信息矩阵，形状为:(K, r, r)，这里相当于分别计算: info + grams[ids[0]]、info + grams[ids[1]]...，特征值结果values的形状: (K, r)
        # values[k]表示，选中的信息矩阵info加上候选的信息矩阵grams[ids[k]]后，各参数方向的信息强度
        values = np.maximum(np.linalg.eigvalsh(info + grams[ids]), 0.)
        # values最后一列特征值最大，乘上1e-8后作为阈值，按行计算有效秩，形状为(K，)
        ranks = np.sum(values > np.maximum(1e-20, values[:, -1:]*1e-8), axis=1)
        # 计算整体信息量评分，对每个特征值加上小正数ridge，对于特征值为0的情况，避免评分出现负无穷，按行求和从(K，r)变为(K，)
        scores = np.sum(np.log(values + ridge), axis=1)
        # 选出最佳候选，先比较ranks，再比较scores
        best = ids[np.lexsort((scores, ranks))[-1]]
        # 更新集合
        chosen.append(pool[best])
        info += grams[best]
        available[best] = False
    # 按照关节id从大到小排列
    chosen.sort(key=lambda s: -s['joint'])
    # 计算回归矩阵，计算回归矩阵的秩、最小奇异值、条件数
    result = metrics(matrix(chosen, cfg, gravity), basis)
    if result['rank'] != r:
        raise ValueError(f'选出的扫描只有秩{result["rank"]}/{r}，请增加--count或--candidates!!!')
    return chosen, dict(before=metrics(matrix(plan['sweeps'], cfg, gravity), basis), after=result, candidates=len(pool), reference_residual=float(residual))

# 将plan排版成要求的格式
def format_plan(plan):
    text = yaml.safe_dump({k: v for k, v in plan.items() if k != 'sweeps'}, sort_keys = False, allow_unicode = True)
    text += 'sweeps:\n'
    counts = {}
    for sweep in plan['sweeps']:
        joint = sweep['joint']
        counts[joint] = counts.get(joint, 0)+1
        text += f"  # 关节{joint}，姿态{counts[joint]}\n  - joint: {joint}\n"
        for key, value in sweep.items():
            if key != 'joint':
                value = yaml.safe_dump(value, default_flow_style=True, width=10000, allow_unicode=True).strip()
                text += f'    {key}: {value}\n'
        text += '\n'
    return text

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config', type=Path, default=ROOT/'config.yaml')
    parser.add_argument('--plan', type=Path, default=ROOT/'plan.yaml', help='继承速度、各轴扫描范围和采样点')
    parser.add_argument('--output', type=Path, default=ROOT/'plan_optimized.yaml')
    parser.add_argument('--side', action='store_true', help='侧装，与采集端一致')
    parser.add_argument('--count', type=int, default=42, help='扫描任务总数，不强制各轴数量相同')
    parser.add_argument('--candidates', type=int, default=100, help='每种扫描模板生成的随机姿态数')
    parser.add_argument('--seed', type=int, default=42)
    args = parser.parse_args()
    if args.count < 1 or args.candidates < 1:
        parser.error('--count和--candidates必须为正整数!!!')
    if args.output.exists():
        parser.error('输出文件已存在，不覆盖!!!')
    cfg = load_config(args.config)
    plan = validate_plan(yaml.safe_load(args.plan.read_text()), cfg)
    lower = np.asarray(cfg['position_min_deg'], dtype=float)
    upper = np.asarray(cfg['position_max_deg'], dtype=float)
    if (lower.shape != (7,) or upper.shape != (7,) or not np.isfinite([lower, upper]).all() or np.any(lower >= upper)):
        parser.error('配置中的关节上下限必须为7个有限值,且下限小于上限!!!')
    for sweep in plan['sweeps']:
        q = np.asarray(sweep['pose_deg'])
        j = sweep['joint']-1
        if (np.any(q < lower) or np.any(q > upper) or sweep['range_deg'][0] < lower[j] or sweep['range_deg'][1] > upper[j]):
            parser.error('原计划姿态或扫描范围超出配置关节限位!!!')
        if np.any(np.diff(sweep['points_deg']) <= 2*plan['sample_tolerance_deg']):
            parser.error('原计划采样窗口重叠，请先调整采样点或容差!!!')
    chosen, report = optimize(cfg, plan, gravity_vector(cfg, args.side), lower, upper, args.count, args.candidates, args.seed)
    output = dict(plan, sweeps=chosen)
    validate_plan(output, cfg)
    header = (f'# 贪心D-optimal扫描计划，seed={args.seed}，side={args.side}。\n' '# 仅验证参数信息覆盖与角度限制，未验证碰撞和连接路径；不保证全局最优!!!\n')
    with args.output.open('x') as f:
        f.write(header+format_plan(output))
    print(yaml.safe_dump(report, sort_keys=False, allow_unicode=True))
    print(f'已写入{args.output}，共{len(chosen)}次扫描；条件数越小、最小奇异值越大越好。')


if __name__ == '__main__':
    main()
