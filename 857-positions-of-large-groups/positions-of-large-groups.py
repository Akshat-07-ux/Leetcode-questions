class Solution:
    def largeGroupPositions(self, s: str) -> list[list[int]]:
        lef = []
        begin = 0
        l = len(s)

        for i in range(1, l +1):
            if i == l or s[i] != s[begin]:
                if i - begin >= 3:
                    lef.append([begin, i - 1])
                begin = i

        return lef