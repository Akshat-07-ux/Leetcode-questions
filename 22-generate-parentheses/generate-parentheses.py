class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        res = []

        def bt(cur, open_c, close_c):
            if len(cur) == 2 * n:
                res.append(cur)
                return

            if open_c < n:
                bt(cur + '(', open_c + 1, close_c)

            if close_c < open_c:
                bt(cur + ')', open_c, close_c + 1)

        bt("", 0, 0)
        return res