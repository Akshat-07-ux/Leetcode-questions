#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        // Sort the array to make the two-pointer sliding window work
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        int low = 0;
        int high = nums[n - 1] - nums[0];
        int ans = high;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Count pairs with absolute difference <= mid
            int count = 0;
            int left = 0;
            for (int right = 0; right < n; ++right) {
                while (nums[right] - nums[left] > mid) {
                    left++;
                }
                // All pairs between left and right have a distance <= mid
                count += (right - left);
            }
            
            // Binary search adjustment
            if (count >= k) {
                ans = mid;      // mid could be our answer
                high = mid - 1; // Try to find a smaller valid distance
            } else {
                low = mid + 1;  // Distances are too small, increase low
            }
        }
        
        return ans;
    }
};