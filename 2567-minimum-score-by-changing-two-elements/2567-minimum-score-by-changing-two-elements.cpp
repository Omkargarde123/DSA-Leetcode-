#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 3) {
            return 0;
        }

        sort(nums.begin(), nums.end());

        int dropTwoSmallest = nums[n - 1] - nums[2];
        int dropTwoLargest  = nums[n - 3] - nums[0];
        int dropBothEnds    = nums[n - 2] - nums[1];

        return min({dropTwoSmallest, dropTwoLargest, dropBothEnds});
    }
};