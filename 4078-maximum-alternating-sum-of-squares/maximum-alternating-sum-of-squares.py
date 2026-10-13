class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        n = len(nums)
        squared = sorted(x * x for x in nums)
        k = (n + 1) // 2
        return sum(squared[n - k:]) - sum(squared[:n - k])