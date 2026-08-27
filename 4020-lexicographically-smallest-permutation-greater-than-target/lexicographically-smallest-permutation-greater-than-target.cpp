#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Helper function to try building the prefix up to `prefix_len`
        // and picking a strictly greater character at position `prefix_len`.
        auto tryBuild = [&](int prefix_len) -> string {
            vector<int> current_freq = freq;
            string result = "";

            // Step 1: Match target[0...prefix_len-1]
            for (int k = 0; k < prefix_len; ++k) {
                int idx = target[k] - 'a';
                if (current_freq[idx] <= 0) return "";
                current_freq[idx]--;
                result += target[k];
            }

            // Step 2: Choose a character > target[prefix_len] at index prefix_len
            int next_char = -1;
            for (int c = target[prefix_len] - 'a' + 1; c < 26; ++c) {
                if (current_freq[c] > 0) {
                    next_char = c;
                    break;
                }
            }

            if (next_char == -1) return "";

            result += (char)('a' + next_char);
            current_freq[next_char]--;

            // Step 3: Append all remaining available characters in ascending order
            for (int c = 0; c < 26; ++c) {
                while (current_freq[c] > 0) {
                    result += (char)('a' + c);
                    current_freq[c]--;
                }
            }

            return result;
        };

        // Try to maximize the matched prefix length (from n-1 down to 0)
        for (int i = n - 1; i >= 0; --i) {
            string res = tryBuild(i);
            if (!res.empty()) {
                return res;
            }
        }

        return "";
    }
};