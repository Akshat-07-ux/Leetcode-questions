class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        win = [0] * k
        dp = [0] * k

        for num in nums:
            n_dp = [0] * k
            rem = num % k
            n_dp[rem] += 1

            for i in range(k):
                if dp[i] > 0:
                    n_mod = (i * rem) % k
                    n_dp[n_mod] += dp[i]

            for i in range(k):
                win[i] += n_dp[i]

            dp = n_dp

        return win