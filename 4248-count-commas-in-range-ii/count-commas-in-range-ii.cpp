class Solution {
public:
    long long countCommas(long long n) {
        long long totalCommas = 0;
        long long power = 1000;
        while (power <= n) {
            totalCommas += (n - power + 1);
            power *= 1000;
        }
        return totalCommas;
    }
};