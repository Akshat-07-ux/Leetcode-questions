#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    double largestSumOfAverages(std::vector<int>& nums, int k) {
        int n = nums.size();
        
        // Compute prefix sums for O(1) subarray sum queries
        std::vector<double> prefix(n + 1, 0.0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // dp[i] will store the max score for nums[0..i-1]
        std::vector<double> dp(n + 1, 0.0);
        
        // Base case: 1 partition (average of nums[0..i-1])
        for (int i = 1; i <= n; ++i) {
            dp[i] = prefix[i] / i;
        }

        // Fill DP table for 2 to k partitions
        for (int p = 2; p <= k; ++p) {
            std::vector<double> next_dp(n + 1, 0.0);
            for (int i = p; i <= n; ++i) {
                for (int j = p - 1; j < i; ++j) {
                    double current_avg = (prefix[i] - prefix[j]) / (i - j);
                    next_dp[i] = std::max(next_dp[i], dp[j] + current_avg);
                }
            }
            dp = std::move(next_dp);
        }

        return dp[n];
    }
};