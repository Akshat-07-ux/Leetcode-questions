#include <vector>
#include <bitset>
#include <algorithm>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        // Step 1: Extract unique elements from nums
        std::vector<int> U = nums;
        std::sort(U.begin(), U.end());
        U.erase(std::unique(U.begin(), U.end()), U.end());

        // Step 2: Compute all pair XOR values (a ^ b)
        std::bitset<2048> s2;
        for (int i = 0; i < U.size(); ++i) {
            for (int j = i; j < U.size(); ++j) {
                s2.set(U[i] ^ U[j]);
            }
        }

        // Step 3: Compute all triplet XOR values (s2_val ^ c)
        std::bitset<2048> s3;
        for (int x = 0; x < 2048; ++x) {
            if (s2[x]) {
                for (int c : U) {
                    s3.set(x ^ c);
                }
            }
        }

        return s3.count();
    }
};