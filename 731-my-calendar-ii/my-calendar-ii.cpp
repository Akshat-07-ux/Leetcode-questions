#include <vector>
#include <algorithm>

using namespace std;

class MyCalendarTwo {
private:
    vector<pair<int, int>> bookings;
    vector<pair<int, int>> overlaps;

public:
    MyCalendarTwo() {
        // Initialization
    }
    
    bool book(int startTime, int endTime) {
        // 1. Check if the new interval overlaps with any double-booked intervals (overlaps)
        for (const auto& interval : overlaps) {
            int max_start = max(startTime, interval.first);
            int min_end = min(endTime, interval.second);
            if (max_start < min_end) {
                // An intersection exists, which would cause a triple booking
                return false;
            }
        }

        // 2. Since it's safe, find new double-bookings created by this booking
        for (const auto& interval : bookings) {
            int max_start = max(startTime, interval.first);
            int min_end = min(endTime, interval.second);
            if (max_start < min_end) {
                // Add the overlapping region to overlaps
                overlaps.push_back({max_start, min_end});
            }
        }

        // 3. Add the event to our master list of bookings
        bookings.push_back({startTime, endTime});
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */