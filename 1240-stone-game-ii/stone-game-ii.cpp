#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
    int memo[101][101]; // memo[i][M] stores the max stones a player can get starting from index i with parameter M

    int solve(int i, int M, const vector<int>& suffixSum, int n) {
        // If no piles are left, 0 stones can be taken
        if (i >= n) return 0;

        // If a player can take all remaining piles, take all of them
        if (2 * M >= n - i) return suffixSum[i];

        // Return cached result if already computed
        if (memo[i][M] != 0) return memo[i][M];

        int maxStones = 0;

        // Try taking X piles where 1 <= X <= 2 * M
        for (int X = 1; X <= 2 * M; ++X) {
            // Player takes 'suffixSum[i] - suffixSum[i + X]' stones.
            // The next player will maximize their stones from position (i + X) with new M = max(M, X).
            // Remaining stones available for current player from (i + X) is suffixSum[i + X] - solve(i + X, max(M, X)).
            int currentTake = suffixSum[i] - solve(i + X, max(M, X), suffixSum, n);
            maxStones = max(maxStones, currentTake);
        }

        return memo[i][M] = maxStones;
    }

public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // Suffix sum array where suffixSum[i] is the total stones from index i to n-1
        vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // Initialize memoization array
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                memo[i][j] = 0;
            }
        }

        return solve(0, 1, suffixSum, n);
    }
};