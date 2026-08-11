#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];
        
        // 1. Calculate the sum of the longest sequential prefix
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break; // Sequential prefix ends
            }
        }
        
        // 2. Put all array elements in a set for O(1) lookup
        unordered_set<int> present(nums.begin(), nums.end());
        
        // 3. Increment sum until we find an integer missing from nums
        while (present.count(sum)) {
            sum++;
        }
        
        return sum;
    }
};