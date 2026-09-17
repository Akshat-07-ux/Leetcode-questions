class Solution:
    def minSumOfLengths(self, arr: List[int], target: int) -> int:
        l = len(arr)

        dp = [float('inf')] * l

        pref_s_m = {0: -1}
        c_sum = 0
        m_l = float('inf')
        win = float('inf')

        for i in range(l):
            c_sum += arr[i]
            need = c_sum - target

            if need in pref_s_m:
                srt_in = pref_s_m[need]
                c_l = i - srt_in

                if srt_in >= 0 and dp[srt_in] != float('inf'):
                    win = min(win, c_l + dp[srt_in])

                m_l = min(m_l, c_l)

            dp[i] = m_l
            pref_s_m[c_sum] = i

        return win if win != float('inf') else -1
        