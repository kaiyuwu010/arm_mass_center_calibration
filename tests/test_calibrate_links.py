import copy
import importlib.util
import json
import subprocess
import sys
import tempfile
from pathlib import Path
import unittest

import numpy as np
import yaml

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("calibrate_links", ROOT/"calibrate_links.py")
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)


class CalibrationTest(unittest.TestCase):
    def setUp(self):
        self.cfg = yaml.safe_load((ROOT/"config.yaml").read_text())["arm_driver"]["ros__parameters"]
        self.cfg["drag"]["torque_permille_per_nm"] = [1000.]*7
        mass = np.array(self.cfg["drag"]["link_mass_kg"])
        com = np.array(self.cfg["drag"]["link_com_m"]).reshape(7, 3)
        self.params = np.column_stack([mass, mass[:, None]*com]).ravel()

    def test_gravity_against_independent_urdf_reference(self):
        expected = [0, 3.10727183916, .398394436107, .433733933214,
                    .001896597324, .001630052759, -.001661442317]
        Y = m.regressor([10, -20, 30, 40, -50, 60, -70], self.cfg, [0, 0, -9.81])
        np.testing.assert_allclose(Y@self.params, expected, atol=1e-4)
        # 自身轴对本连杆质量和轴向一阶矩不可观测。
        for j in range(7):
            self.assertAlmostEqual(Y[j, 4*j], 0.)
            self.assertAlmostEqual(Y[j, 4*j+3], 0.)

    def test_motion_has_matching_cruise_and_rest_endpoints(self):
        q0, q1 = np.zeros(7), np.zeros(7)
        q1[6] = 20
        t, q, flat = m.motion(q0, q1, .5, 3., .01)
        np.testing.assert_allclose(q[0], q0)
        np.testing.assert_allclose(q[-1], q1)
        v = np.diff(q[:, 6])/np.diff(t)
        mask = (t[:-1] > flat[0]+.1) & (t[:-1] < flat[1]-.1)
        np.testing.assert_allclose(v[mask], .5, atol=1e-10)
        _, reverse, _ = m.motion(q1, q0, .5, 3., .01)
        np.testing.assert_allclose(reverse[:, 6], 20-q[:, 6], atol=1e-10)
        # 差分速度是首末采样区间的平均速度，恒加减速时为a*dt/2。
        self.assertAlmostEqual(v[0], (.5/3.)*(t[1]-t[0])/2)
        self.assertAlmostEqual(v[-1], (.5/3.)*(t[-1]-t[-2])/2)

    def test_bidirectional_pairing_and_rank_deficiency(self):
        rng = np.random.default_rng(42)
        sweeps, raw = [], []
        g = np.array([-9.81, 0, 0])
        actual = self.params.copy()
        actual[25] += .002
        for j in range(7, 0, -1):
            for _ in range(5):
                pose = rng.uniform(-60, 60, 7)
                sid = len(sweeps)
                sweeps.append(dict(joint=j, pose_deg=pose.tolist(), range_deg=[-20, 20], points_deg=[-10, 0, 10]))
                for point in [-10, 0, 10]:
                    for direction in [1, -1]:
                        for offset in [-.05, 0, .05]:
                            q = pose.copy(); q[j-1] = point+offset
                            v = np.zeros(7); v[j-1] = direction*.5
                            torque = m.regressor(q, self.cfg, g)@actual
                            torque[j-1] += direction*.3  # 对称摩擦
                            raw.append(dict(sweep=sid, direction=direction, q=q.tolist(), v=v.tolist(), torque=(1000*torque).tolist()))
        plan = m.validate_plan(dict(sweeps=sweeps), self.cfg)
        A, b, metadata = m.paired_rows(raw, plan, self.cfg, g)
        np.testing.assert_allclose(b, A@actual, atol=1e-12)
        report, patch = m.identify(A, b, self.cfg, metadata)
        self.assertLess(report["rmse_nm"], 1e-8)
        self.assertLess(report["stages"][-1]["rank"], 28)
        self.assertIsNotNone(patch)
        # 完整离线入口：读取配置/原始记录，输出报告和候选YAML。
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/"config.yaml").write_text(yaml.safe_dump({"arm_driver": {"ros__parameters": self.cfg}}))
            (root/"plan.yaml").write_text(yaml.safe_dump(plan))
            (root/"raw.jsonl").write_text("\n".join(json.dumps(r) for r in raw))
            subprocess.run([sys.executable, str(ROOT/"calibrate_links.py"), "fit", "--side",
                            "--config", str(root/"config.yaml"), "--plan", str(root/"plan.yaml"),
                            "--data", str(root/"raw.jsonl"), "--output", str(root/"result")],
                           check=True, capture_output=True, text=True)
            saved = json.loads((root/"result/report.json").read_text())
            self.assertLess(saved["rmse_nm"], 1e-8)
            candidate = yaml.safe_load((root/"result/candidate_drag.yaml").read_text())
            self.assertEqual(len(candidate["arm_driver"]["ros__parameters"]["drag"]["link_com_m"]), 21)
        # 不允许单方向数据悄悄参与拟合。
        with self.assertRaises(ValueError):
            m.paired_rows([r for r in raw if r["direction"] == 1], plan, self.cfg, g)
        # 正反向速度不匹配应拒绝。
        mismatched = copy.deepcopy(raw)
        for r in mismatched:
            if r["direction"] == -1:
                r["v"] = (np.array(r["v"])*2).tolist()
        with self.assertRaises(ValueError):
            m.paired_rows(mismatched, plan, self.cfg, g)

    def test_plan_rejects_no_cruise_margin(self):
        with self.assertRaises(ValueError):
            m.validate_plan(dict(sweeps=[dict(joint=7, pose_deg=[0]*7, range_deg=[-1, 1], points_deg=[-.5, 0, .5])]), self.cfg)


if __name__ == "__main__":
    unittest.main()
