#include <vector>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        int n = nums.size();
        
        // Track unique values seen so far, valid pair XORs, and valid triplet XORs
        std::vector<bool> seen(2048, false);
        std::vector<bool> pairXor(2048, false);
        std::vector<bool> tripletXor(2048, false);

        for (int num : nums) {
            // 1. Mark current number as seen
            seen[num] = true;

            // 2. Form new pairs (i, j') where current num acts as nums[j'] (i <= j')
            for (int x = 0; x < 2048; ++x) {
                if (seen[x]) {
                    pairXor[x ^ num] = true;
                }
            }

            // 3. Form new triplets (i, j', k) where current num acts as nums[k] (j' <= k)
            for (int p = 0; p < 2048; ++p) {
                if (pairXor[p]) {
                    tripletXor[p ^ num] = true;
                }
            }
        }

        // Count all achievable unique triplet XOR values
        int count = 0;
        for (int i = 0; i < 2048; ++i) {
            if (tripletXor[i]) {
                count++;
            }
        }

        return count;
    }
};