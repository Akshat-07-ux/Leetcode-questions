#include <vector>

using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        int n = bits.size();
        
        // Traverse the array until the second to last element
        while (i < n - 1) {
            if (bits[i] == 1) {
                // It's a two-bit character, so skip the next bit as well
                i += 2;
            } else {
                // It's a one-bit character, move to the next bit
                i += 1;
            }
        }
        
        // If we ended exactly at the last index, the last character must be a 1-bit character
        return i == n - 1;
    }
};