class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = []
        for char in s:
            if char == ')':
                cur = []
                while stack and stack[-1] != '(':
                    cur.append(stack.pop())

                stack.pop()

                for c in cur:
                    stack.append(c)

            else:
                stack.append(char)

        return "".join(stack)        