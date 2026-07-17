#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> st; // Stores indices of the elements
        
        for (int i = 0; i < n; i++) {
            // While the stack is not empty and the current temperature is 
            // strictly warmer than the temperature at the index on top of the stack
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prev_index = st.top();
                st.pop();
                // The number of days to wait is the difference between indices
                ans[prev_index] = i - prev_index;
            }
            // Push the current day's index onto the stack
            st.push(i);
        }
        
        return ans;
    }
};