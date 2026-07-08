#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;
        
        // Precompute powers of 10 modulo 10^9 + 7
        vector<long long> power10(m + 1, 1);
        for (int i = 1; i <= m; i++) {
            power10[i] = (power10[i - 1] * 10) % MOD;
        }
        
        // prefixX[i] stores the numerical value of non-zero digits up to index i-1
        vector<long long> prefixX(m + 1, 0);
        // prefixCount[i] stores the count of non-zero digits up to index i-1
        vector<int> prefixCount(m + 1, 0);
        // prefixSum[i] stores the sum of digits up to index i-1
        vector<long long> prefixSum(m + 1, 0);
        
        for (int i = 0; i < m; i++) {
            int digit = s[i] - '0';
            
            prefixSum[i + 1] = prefixSum[i] + digit;
            
            if (digit != 0) {
                prefixX[i + 1] = (prefixX[i] * 10 + digit) % MOD;
                prefixCount[i + 1] = prefixCount[i] + 1;
            } else {
                prefixX[i + 1] = prefixX[i];
                prefixCount[i + 1] = prefixCount[i];
            }
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            
            // 1. Calculate sum of digits in the range [l, r]
            long long current_sum = prefixSum[r + 1] - prefixSum[l];
            
            // 2. Calculate the value of x formed by non-zero digits in [l, r]
            int nonZeroCount = prefixCount[r + 1] - prefixCount[l];
            
            long long x = 0;
            if (nonZeroCount > 0) {
                long long mapped_left = (prefixX[l] * power10[nonZeroCount]) % MOD;
                x = (prefixX[r + 1] - mapped_left + MOD) % MOD;
            }
            
            // 3. Compute final answer for the query
            long long current_ans = (x * (current_sum % MOD)) % MOD;
            answer.push_back(current_ans);
        }
        
        return answer;
    }
};