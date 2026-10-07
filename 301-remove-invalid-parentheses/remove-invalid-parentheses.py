class Solution:
    def removeInvalidParentheses(self, s: str) -> list[str]:

        def is_valid(st):
            cnt = 0
            for c in st:
                if c == '(':
                    cnt += 1
                elif c == ')':
                    cnt -= 1
                    if cnt < 0:
                        return False
            return cnt == 0

        res = []
        visited = {s}

        q = [s]
        found = False

        while q:
            nxt = []
            for curr in q:
                if is_valid(curr):
                    res.append(curr)
                    found = True

                if found:
                    continue

                for i in range(len(curr)):
                    if curr[i] not in '()':
                        continue

                    candidate = curr[:i] + curr[i+1:]
                    if candidate not in visited:
                        visited.add(candidate)
                        nxt.append(candidate)

            if found:
                break
            q = nxt

        return res
        