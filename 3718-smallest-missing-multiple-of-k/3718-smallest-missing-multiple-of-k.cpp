#include <unordered_set>
#include <vector>

class Solution {
public:
    int missingMultiple(std::vector<int>& nums, int k) {
        std::unordered_set<int> seen(nums.begin(), nums.end());
        
        int multiple = k;
        while (seen.count(multiple)) {
            multiple += k;
        }
        
        return multiple;
    }
};