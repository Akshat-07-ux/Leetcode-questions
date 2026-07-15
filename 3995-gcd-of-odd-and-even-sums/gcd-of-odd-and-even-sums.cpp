#include <numeric>

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        // sumOdd = n * n
        // sumEven = n * (n + 1)
        // GCD(n*n, n*(n+1)) will always evaluate to n
        return n;
    }
};