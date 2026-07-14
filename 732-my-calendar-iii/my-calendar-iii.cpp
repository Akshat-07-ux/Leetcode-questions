#include <map>
#include <algorithm>

using namespace std;

class MyCalendarThree {
private:
    // map to store time points and their corresponding net change in events
    map<int, int> timeline;

public:
    MyCalendarThree() {
        // Initialization
    }
    
    int book(int startTime, int endTime) {
        // Mark the start of a new event
        timeline[startTime]++;
        // Mark the end of the event
        timeline[endTime]--;
        
        int max_k = 0;
        int current_bookings = 0;
        
        // Sweep across the timeline in chronological order
        for (const auto& [time, change] : timeline) {
            current_bookings += change;
            max_k = max(max_k, current_bookings);
        }
        
        return max_k;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */