#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int max_val = *max_element(nums.begin(), nums.end());
        
        // sum_buckets[x] will store the total points we can get from all occurrences of value x
        vector<int> sum_buckets(max_val + 1, 0);
        for (int num : nums) {
            sum_buckets[num] += num;
        }
        
        // Dynamic programming variables (House Robber style optimization)
        int prev2 = 0; // Represents maximum points up to x - 2
        int prev1 = 0; // Represents maximum points up to x - 1
        
        for (int i = 0; i <= max_val; i++) {
            // At each step, we decide whether to take the current value (and skip the previous) 
            // or skip the current value (and keep the previous max)
            int current = max(prev1, prev2 + sum_buckets[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};