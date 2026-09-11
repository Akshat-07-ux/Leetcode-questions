from collections import Counter

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        have = Counter(digits)
        total = 0

        for num in range(100, 1000, 2):
            r = num
            need =  Counter()
            while r > 0:
                r, left = divmod(r, 10)
                need[left] += 1

            if all(have[z] >= req for z, req in need.items()):
                total += 1
        return total
        