#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
        // Sort words lexicographically
        sort(words.begin(), words.end());
        
        unordered_set<string> built_words;
        string result = "";
        
        for (const string& word : words) {
            // A word is valid if it's 1 char long OR its prefix exists in the set
            if (word.length() == 1 || built_words.count(word.substr(0, word.length() - 1))) {
                built_words.insert(word);
                
                // Update result if we find a strictly longer word
                if (word.length() > result.length()) {
                    result = word;
                }
            }
        }
        
        return result;
    }
};