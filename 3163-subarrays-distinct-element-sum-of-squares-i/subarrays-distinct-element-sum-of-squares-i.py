class Solution:
    def sumCounts(self, nums: List[int]) -> int:
        n = len(nums)
        total_sum = 0

        for i in range(n):
            seen_element = set()

            for j in range(i, n):
                seen_element.add(nums[j])
                distinct_count = len(seen_element)
                total_sum += distinct_count * distinct_count

        return total_sum