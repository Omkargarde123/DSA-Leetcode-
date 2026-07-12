#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    std::vector<int> arrayRankTransform(std::vector<int>& arr) {
        std::vector<int> sorted_arr = arr;
        std::sort(sorted_arr.begin(), sorted_arr.end());
        
        std::unordered_map<int, int> ranks;
        int rank = 1;
        
        for (int num : sorted_arr) {
            // Only assign a rank if the element hasn't been seen yet
            if (ranks.find(num) == ranks.end()) {
                ranks[num] = rank;
                rank++;
            }
        }
        
        // Replace elements in the original array with their ranks
        for (int& num : arr) {
            num = ranks[num];
        }
        
        return arr;
    }
};