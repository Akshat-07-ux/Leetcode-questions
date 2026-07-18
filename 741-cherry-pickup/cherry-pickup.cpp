#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // dp[r1][r2] will store the max cherries at the current step `t`
        // We initialize with -1 to represent unreached or invalid states.
        vector<vector<int>> dp(n, vector<int>(n, -1));
        dp[0][0] = grid[0][0];

        // Total steps to go from (0,0) to (n-1, n-1) is 2 * (n - 1)
        int max_steps = 2 * (n - 1);

        for (int t = 1; t <= max_steps; ++t) {
            // next_dp will hold states for the next step t
            vector<vector<int>> next_dp(n, vector<int>(n, -1));

            // Iterate through all possible row combinations for person 1 and person 2
            for (int r1 = 0; r1 < n; ++r1) {
                for (int r2 = 0; r2 < n; ++r2) {
                    int c1 = t - r1;
                    int c2 = t - r2;

                    // Out of bounds check
                    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) continue;

                    // Blocked by a thorn
                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;

                    // Look at the 4 possible previous steps that led to this state:
                    // 1. Both moved Right: (r1, r2)
                    // 2. Person 1 moved Down, Person 2 moved Right: (r1-1, r2)
                    // 3. Person 1 moved Right, Person 2 moved Down: (r1, r2-1)
                    // 4. Both moved Down: (r1-1, r2-1)
                    int max_prev = -1;
                    
                    if (dp[r1][r2] != -1) max_prev = max(max_prev, dp[r1][r2]);
                    if (r1 > 0 && dp[r1 - 1][r2] != -1) max_prev = max(max_prev, dp[r1 - 1][r2]);
                    if (r2 > 0 && dp[r1][r2 - 1] != -1) max_prev = max(max_prev, dp[r1][r2 - 1]);
                    if (r1 > 0 && r2 > 0 && dp[r1 - 1][r2 - 1] != -1) max_prev = max(max_prev, dp[r1 - 1][r2 - 1]);

                    // If none of the previous steps were reachable, this state is unreachable
                    if (max_prev == -1) continue;

                    // Add cherries at current cells. If they land on the same spot, only count once.
                    int cherries = 0;
                    if (r1 == r2) {
                        cherries = grid[r1][c1];
                    } else {
                        cherries = grid[r1][c1] + grid[r2][c2];
                    }

                    next_dp[r1][r2] = max_prev + cherries;
                }
            }
            dp = move(next_dp);
        }

        // Return 0 if the destination was never successfully reached
        return max(0, dp[n - 1][n - 1]);
    }
};