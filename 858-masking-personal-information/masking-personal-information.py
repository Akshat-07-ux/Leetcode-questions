class Solution:
    def maskPII(self, s: str) -> str:
        if '@' in s:
            name, domain = s.lower().split('@')

            return name[0] + '*****' + name[-1] + '@' + domain

        else:
            digits = ''.join(c for c in s if c.isdigit())
            local = digits[-4:]
            country_len = len(digits) - 10

            if country_len == 0:
                return '***-***-' + local

            else:
                return '+' + '*' * country_len + '-***-***-' + local