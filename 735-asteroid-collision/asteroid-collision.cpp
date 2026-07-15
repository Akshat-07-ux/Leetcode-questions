#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st; // Use a vector as a stack for easy conversion to output

        for (int ast : asteroids) {
            bool exploded = false;

            // Collision only happens when stack top is moving right (+) and current is moving left (-)
            while (!st.empty() && st.back() > 0 && ast < 0) {
                if (st.back() < abs(ast)) {
                    // The right-moving asteroid at the top is smaller, it explodes.
                    st.pop_back();
                    continue; // Continue checking with the next elements in the stack
                } else if (st.back() == abs(ast)) {
                    // Both are of the same size, both explode.
                    st.pop_back();
                    exploded = true;
                    break;
                } else {
                    // The right-moving asteroid is larger, current asteroid explodes.
                    exploded = true;
                    break;
                }
            }

            // If the current asteroid did not explode, push it to the stack
            if (!exploded) {
                st.push_back(ast);
            }
        }

        return st;
    }
};