#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> heights(n);
        vector<int> ans(n);
        
        int current_max = 0;
        
        for (int i = 0; i < n; ++i) {
            int left = positions[i][0];
            int size = positions[i][1];
            int right = left + size;
            
            // Base height if it lands directly on the X-axis
            int base_height = 0;
            
            // Check all previously dropped squares for intervals overlapping with [left, right)
            for (int j = 0; j < i; ++j) {
                int prev_left = positions[j][0];
                int prev_size = positions[j][1];
                int prev_right = prev_left + prev_size;
                
                // Overlap condition for open intervals: max(left1, left2) < min(right1, right2)
                if (max(left, prev_left) < min(right, prev_right)) {
                    base_height = max(base_height, heights[j]);
                }
            }
            
            // Total height of the current square after landing
            heights[i] = base_height + size;
            
            // Update the global running maximum height seen so far
            current_max = max(current_max, heights[i]);
            ans[i] = current_max;
        }
        
        return ans;
    }
};