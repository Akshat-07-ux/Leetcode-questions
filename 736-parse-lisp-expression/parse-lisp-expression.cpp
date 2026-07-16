#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
private:
    // Helper function to parse tokens while respecting nested parentheses
    vector<string> parse(const string& str) {
        vector<string> res;
        int n = str.length();
        int balance = 0;
        string current = "";
        
        for (int i = 0; i < n; ++i) {
            if (str[i] == '(') balance++;
            if (str[i] == ')') balance--;
            
            if (str[i] == ' ' && balance == 0) {
                if (!current.empty()) {
                    res.push_back(current);
                    current = "";
                }
            } else {
                current += str[i];
            }
        }
        if (!current.empty()) {
            res.push_back(current);
        }
        return res;
    }

    int eval(string exp, vector<unordered_map<string, int>>& scope) {
        // If it's not a sub-expression enclosed in parentheses
        if (exp[0] != '(') {
            // Check if it's a number (can be negative, so check digits or length)
            if (isdigit(exp[0]) || exp[0] == '-') {
                return stoi(exp);
            }
            // Otherwise, it's a variable name. Look it up from innermost to outermost scope.
            for (int i = scope.size() - 1; i >= 0; --i) {
                if (scope[i].count(exp)) {
                    return scope[i][exp];
                }
            }
            return 0; // Fallback (should not be reached per constraints)
        }

        // Strip the outermost parentheses: "(let x 2 x)" -> "let x 2 x"
        string stripped = exp.substr(1, exp.length() - 2);
        vector<string> tokens = parse(stripped);
        
        string type = tokens[0];
        
        if (type == "add") {
            return eval(tokens[1], scope) + eval(tokens[2], scope);
        } 
        else if (type == "mult") {
            return eval(tokens[1], scope) * eval(tokens[2], scope);
        } 
        else { // type == "let"
            // Push a new scope layer for this let block
            scope.push_back(unordered_map<string, int>());
            
            // Loop through the pairs. The last element (tokens.size() - 1) is the actual expression.
            for (size_t i = 1; i < tokens.size() - 1; i += 2) {
                string var = tokens[i];
                int val = eval(tokens[i + 1], scope);
                scope.back()[var] = val; // Assign/overwrite in the current innermost scope
            }
            
            // Evaluate the final value expression of this let block
            int ans = eval(tokens.back(), scope);
            
            // Pop the scope layer before returning
            scope.pop_back();
            return ans;
        }
    }

public:
    int evaluate(string expression) {
        vector<unordered_map<string, int>> scope;
        return eval(expression, scope);
    }
};