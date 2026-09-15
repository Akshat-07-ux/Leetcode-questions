class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        count = [0] * 121
        for age in ages:
            count[age] += 1

        total = 0
        for i in range(1, 121):
            if count[i] == 0:
                continue

            for j in range(1, 121):
                if count[j] == 0:
                    continue
                if j <= 0.5 * i + 7:
                    continue
                if j > i:
                    continue
                if j > 100 and i < 100:
                    continue

                total += count[i] * count[j]
                if i == j:
                    total -= count[i]

        return total
        