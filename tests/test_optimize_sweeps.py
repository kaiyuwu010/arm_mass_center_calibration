import sys
import unittest
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from calibrate_links import sample_points
from optimize_sweeps import information_metrics, select_balanced, format_plan


class PlanningTest(unittest.TestCase):
    def test_five_degree_grid_excludes_transition_regions(self):
        plan = dict(speed_deg_s=10., ramp_s=1., settle_s=.2, stable_s=.2,
                    sample_tolerance_deg=.8)
        for limits, first, count in [([-30, 30], -20.2, 9), ([-15, 120], -5.2, 24)]:
            sweep = dict(joint=2, pose_deg=[0]*7, range_deg=limits, points_deg=[999])
            points = sample_points(sweep, plan)
            self.assertEqual(len(points), count)
            self.assertAlmostEqual(points[0], first+1e-6)
            np.testing.assert_allclose(np.diff(points), 5.)
            self.assertGreater(points[0], limits[0]+9.8)
            self.assertLess(points[-1], limits[1]-9.8)
        self.assertEqual(sample_points(dict(range_deg=[-1, 1]), plan), [])

    def test_equal_counts_score_improvement_and_local_optimum(self):
        rng = np.random.default_rng(12)
        joints = np.repeat(np.arange(1, 8), 5)
        blocks = rng.normal(size=(35, 2, 4))
        grams = np.array([b.T@b for b in blocks])
        selected, report = select_balanced(grams, joints, 14)
        self.assertEqual(len(set(selected)), 14)
        self.assertTrue(np.all(np.bincount(joints[selected], minlength=8)[1:] == 2))
        self.assertGreater(report['swaps'], 0)
        self.assertGreater(report['final_score'], report['initial_score'])
        ridge = max(np.trace(grams, axis1=1, axis2=2).max()*1e-8, 1e-12)
        info = grams[selected].sum(axis=0)
        r, score = information_metrics(info, ridge)
        self.assertGreaterEqual(r, report['initial_rank'])
        for old in selected:
            for new in set(range(len(grams)))-set(selected):
                if joints[new] != joints[old]:
                    continue
                new_rank, new_score = information_metrics(info-grams[old]+grams[new], ridge)
                self.assertFalse(new_rank >= r and new_score > score+1e-9)
        for count in [0, 8, 42]:
            with self.assertRaises(ValueError):
                select_balanced(grams, joints, count)
        with self.assertRaises(ValueError):
            select_balanced(grams[joints != 7], joints[joints != 7], 7)


if __name__ == '__main__':
    unittest.main()
