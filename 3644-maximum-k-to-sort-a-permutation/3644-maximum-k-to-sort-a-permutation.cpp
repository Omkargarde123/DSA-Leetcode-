#include <vector>
#include <bit>

class Solution {
public:
    int sortPermutation(std::vector<int>& nums) {
        unsigned n = nums.size();
        int k0 = std::bit_ceil(n) - 1; // All bits set mask
        int k = k0;
        
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if (x != i) {
                k &= x;
            }
        }
        
        return (k == k0) ? 0 : k;
    }
};
