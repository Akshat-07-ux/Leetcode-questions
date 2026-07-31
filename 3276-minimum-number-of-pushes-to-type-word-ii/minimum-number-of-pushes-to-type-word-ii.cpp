class Solution {
public:
    int minimumPushes(string word) {
        // Step 1: Count frequency of each letter
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }
        
        // Step 2: Sort frequencies in descending order
        sort(freq.rbegin(), freq.rend());
        
        // Step 3: Calculate total key pushes greedily
        int totalPushes = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) break; // No more characters present in word
            
            int pushesPerChar = (i / 8) + 1; // Position 1 for first 8, position 2 for next 8, etc.
            totalPushes += freq[i] * pushesPerChar;
        }
        
        return totalPushes;
    }
};