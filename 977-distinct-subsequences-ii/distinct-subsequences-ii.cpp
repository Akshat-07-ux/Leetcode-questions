class Solution {
public:
    int distinctSubseqII(string s) {
        long long MOD = 1e9 + 7;
        vector<long long> last(26, 0);
        long long total = 0;
        
        for (char c : s) {
            int idx = c - 'a';
            long long added = (total + 1 - last[idx] + MOD) % MOD;
            total = (total + added) % MOD;
            last[idx] = (last[idx] + added) % MOD;
        }
        
        return total;
    }
};