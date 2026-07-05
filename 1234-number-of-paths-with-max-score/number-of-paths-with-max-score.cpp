#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        // dp_score[i][j] stores the max score to reach (i, j) from 'S'
        // Initialize with -1 to represent unreachable states
        vector<vector<int>> dp_score(n, vector<int>(n, -1));
        // dp_paths[i][j] stores the number of paths to get the max score at (i, j)
        vector<vector<int>> dp_paths(n, vector<int>(n, 0));
        
        // Base case: Start at the bottom-right corner 'S'
        dp_score[n - 1][n - 1] = 0;
        dp_paths[n - 1][n - 1] = 1;
        
        // Directions to look back to: Right, Down, Down-Right
        int dirs[3][2] = {{0, 1}, {1, 0}, {1, 1}};
        
        // Process the board from bottom-right to top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Skip if it's an obstacle or the starting point itself (already initialized)
                if (board[i][j] == 'X' || (i == n - 1 && j == n - 1)) {
                    continue;
                }
                
                int max_s = -1;
                int path_count = 0;
                
                // Check all 3 valid previous steps
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    // If the neighbor is within bounds and reachable
                    if (ni < n && nj < n && dp_score[ni][nj] != -1) {
                        if (dp_score[ni][nj] > max_s) {
                            max_s = dp_score[ni][nj];
                            path_count = dp_paths[ni][nj];
                        } else if (dp_score[ni][nj] == max_s) {
                            path_count = (path_count + dp_paths[ni][nj]) % MOD;
                        }
                    }
                }
                
                // If this cell is reachable from at least one valid path
                if (max_s != -1) {
                    int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp_score[i][j] = max_s + current_val;
                    dp_paths[i][j] = path_count;
                }
            }
        }
        
        // If 'E' at (0,0) is unreachable, return [0, 0]
        if (dp_score[0][0] == -1) {
            return {0, 0};
        }
        
        return {dp_score[0][0], dp_paths[0][0]};
    }
};