class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        mod = 10**9 + 7
        bits = [0] * 31

        for val in nums:
            for i in range(31):
                if (val >> i) & 1:
                    bits[i] += 1

        res = 0
        for _ in range(k):
            curr = 0

            for i in range(30, -1, -1):
                if bits[i] > 0:
                    curr |= (1 << i)

                    bits[i] -= 1

            res = (res + curr * curr) % mod

        return res
