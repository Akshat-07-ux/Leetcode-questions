class Solution {
public:
    string reorganizeString(string s) {
        vector<int> freq(26, 0);
        int maxFreq = 0;
        char maxChar = 'a';
        
        // Count frequencies and identify the most frequent character
        for (char c : s) {
            freq[c - 'a']++;
            if (freq[c - 'a'] > maxFreq) {
                maxFreq = freq[c - 'a'];
                maxChar = c;
            }
        }

        int n = s.length();
        // If the most frequent character occurs more than (n + 1) / 2 times,
        // it's impossible to avoid adjacent duplicates.
        if (maxFreq > (n + 1) / 2) {
            return "";
        }

        string res(n, ' ');
        int idx = 0;

        // Place the most frequent character into even indices first (0, 2, 4, ...)
        while (freq[maxChar - 'a'] > 0) {
            res[idx] = maxChar;
            idx += 2;
            freq[maxChar - 'a']--;
        }

        // Place the remaining characters into the remaining even indices,
        // then switch to odd indices (1, 3, 5, ...)
        for (int i = 0; i < 26; ++i) {
            while (freq[i] > 0) {
                if (idx >= n) {
                    idx = 1; // Switch to odd positions once evens are filled
                }
                res[idx] = 'a' + i;
                idx += 2;
                freq[i]--;
            }
        }

        return res;
    }
};