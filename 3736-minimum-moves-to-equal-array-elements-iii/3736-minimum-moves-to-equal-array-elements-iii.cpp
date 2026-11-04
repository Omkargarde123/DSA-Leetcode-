#include <vector>
#include <algorithm>
#include <numeric>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int max_val = *std::max_element(nums.begin(), nums.end());
        int moves = 0;
        for (int num : nums) {
            moves += (max_val - num);
        }
        return moves;
    }
};