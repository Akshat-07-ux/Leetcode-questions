from bisect import bisect_left
from typing import List

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)

        ind_int = sorted(
            (intervals[i][1], intervals[i][0], intervals[i][2], i)
            for i in range(n)
        )

        ends = [item[0] for item in ind_int]

        dp = [[(0, ()) for _ in range(n + 1)] for _ in range(5)]

        for k in range(1, 5):
            for j in range(1, n + 1):
                bt = dp[k][j - 1]

                end_value, start_value, weight_value, origin_index = ind_int[j - 1]

                pre_cnt = bisect_left(ends, start_value)

                pre_neg_wgt, pre_ind = dp[k - 1][pre_cnt]

                new_wgt = -pre_neg_wgt + weight_value
                new_ind = tuple(sorted(pre_ind + (origin_index,)))

                student = (-new_wgt, new_ind)
                if student < bt:
                    bt = student

                dp[k][j] = bt

        bt_chc = dp[0][n]
        for k in range(1,5):
            if dp[k][n] < bt_chc:
                bt_chc = dp[k][n]

        return list(bt_chc[1])


        