#include <vector>

using namespace std;

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // All 8 possible directional moves for a chess knight
        int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

        // dp[r][c] will store the probability of the knight being at (r, c)
        vector<vector<double>> dp(n, vector<double>(n, 0.0));
        
        // Base case: At 0 moves, the knight is safely at the starting cell with probability 1.0
        dp[row][column] = 1.0;

        // Iterate through each move from 1 to k
        for (int step = 0; step < k; ++step) {
            vector<vector<double>> next_dp(n, vector<double>(n, 0.0));

            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    if (dp[r][c] > 0) {
                        // Spread the probability to all 8 possible moves
                        for (int i = 0; i < 8; ++i) {
                            int nr = r + dr[i];
                            int nc = c + dc[i];

                            // Check if the move keeps the knight inside the board
                            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                                next_dp[nr][nc] += dp[r][c] / 8.0;
                            }
                        }
                    }
                }
            }
            // Move to the next state
            dp = move(next_dp);
        }

        // Accumulate all the probabilities left on the board after k moves
        double total_probability = 0.0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                total_probability += dp[r][c];
            }
        }

        return total_probability;
    }
};