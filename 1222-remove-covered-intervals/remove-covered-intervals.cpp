#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Sort intervals:
        // 1. By start point ascending
        // 2. By end point descending if start points are equal
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });
        
        int remaining_count = 0;
        int max_end = 0;
        
        for (const auto& interval : intervals) {
            // If the current interval's end is greater than max_end seen so far,
            // it is not covered by any previous interval.
            if (interval[1] > max_end) {
                remaining_count++;
                max_end = interval[1]; // Update the maximum reaching boundary
            }
        }
        
        return remaining_count;
    }
};