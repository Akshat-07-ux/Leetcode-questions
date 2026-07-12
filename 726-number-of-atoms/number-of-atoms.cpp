#include <string>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        int n = formula.length();
        // Stack to store element frequencies at different parenthesis levels
        vector<map<string, int>> st;
        st.push_back(map<string, int>()); // Base map for the global scope
        
        int i = 0;
        while (i < n) {
            if (formula[i] == '(') {
                // Start a new scope level
                st.push_back(map<string, int>());
                i++;
            } 
            else if (formula[i] == ')') {
                i++;
                // Check if a multiplier count follows the closing parenthesis
                int start = i;
                while (i < n && isdigit(formula[i])) {
                    i++;
                }
                int multiplicity = 1;
                if (i > start) {
                    multiplicity = stoi(formula.substr(start, i - start));
                }
                
                // Pop the top map (current scope) and merge it with the parent scope
                map<string, int> top = st.back();
                st.pop_back();
                
                for (auto& pair : top) {
                    st.back()[pair.first] += pair.second * multiplicity;
                }
            } 
            else {
                // Parse the chemical element name (Uppercase + zero or more lowercase)
                int start = i;
                i++; // Consume uppercase letter
                while (i < n && islower(formula[i])) {
                    i++;
                }
                string name = formula.substr(start, i - start);
                
                // Parse the optional count following the element name
                start = i;
                while (i < n && isdigit(formula[i])) {
                    i++;
                }
                int count = 1;
                if (i > start) {
                    count = stoi(formula.substr(start, i - start));
                }
                
                // Add to the current top scope
                st.back()[name] += count;
            }
        }
        
        // The last remaining map in the stack contains the total sorted counts
        string result = "";
        for (auto& pair : st.back()) {
            result += pair.first;
            if (pair.second > 1) {
                result += to_string(pair.second);
            }
        }
        
        return result;
    }
};