#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Precompute the minimums from right to left (suffix minimums)
        vector<int> suf_min(n);
        suf_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suf_min[i] = min(suf_min[i + 1], nums[i]);
        }
        
        int pref_max = -1; // Since nums[i] >= 0, starting with -1 is safe
        
        // Traverse left to right, maintaining the prefix maximum
        for (int i = 0; i < n; ++i) {
            pref_max = max(pref_max, nums[i]);
            
            // Check if the current index is stable
            if (pref_max - suf_min[i] <= k) {
                return i;
            }
        }
        
        // No stable index found
        return -1;
    }
};