class Solution:
    def maxDepthAfterSplit(self, seq: str) -> list[int]:
        win = []
        ms = 0

        for s in seq:
            if s == '(':
                ms += 1
            win.append(ms % 2)
            if s == ')':
                ms -= 1
        
        return win