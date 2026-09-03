#include <vector>
#include <algorithm>

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1) {
        int minVal = nums1[0];
        bool hasOdd = false;

        for (int x : nums1) {
            if (x < minVal) {
                minVal = x;
            }
            if (x % 2 != 0) {
                hasOdd = true;
            }
        }

        // Case 1: No odd numbers present -> can be all even.
        if (!hasOdd) return true;

        // Case 2: Minimum element is odd -> can make all elements odd.
        if (minVal % 2 != 0) return true;

        // Otherwise impossible.
        return false;
    }
};