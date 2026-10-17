class Solution:
    def minSwaps(self, nums: List[int]) -> int:

        def get_digit_sum(x):
            total = 0
            while x > 0:
                total += x % 10
                x //= 10
            return total

        n = len(nums)

        indexed_nums = [(get_digit_sum(nums[i]), nums[i], i) for i in range(n)]

        indexed_nums.sort(key=lambda x: (x[0], x[1]))

        target = [0] * n
        for i in range(n):
            target[indexed_nums[i][2]] = i

        visited = [False] * n
        swaps = 0

        for i in range(n):
            if visited[i] or target[i] == i:
                continue

            cycle_size = 0
            curr = i
            while not visited[curr]:
                visited[curr] = True
                curr = target[curr]
                cycle_size += 1

            swaps += (cycle_size - 1)

        return swaps


        