#include <vector>
#include <algorithm>

class Solution {
public:
    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        int ans = 1e9;

        int zeroIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                zeroIdx = i;
                break;
            }
        }

        bool isIncRot = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(zeroIdx + i) % n] != i) {
                isIncRot = false;
                break;
            }
        }

        if (isIncRot) {
            ans = std::min(ans, zeroIdx);
            int rev_shift = (n - zeroIdx) % n;
            ans = std::min(ans, 2 + rev_shift);
        }

        int nMinus1Idx = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == n - 1) {
                nMinus1Idx = i;
                break;
            }
        }

        bool isDecRot = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(nMinus1Idx + i) % n] != (n - 1 - i)) {
                isDecRot = false;
                break;
            }
        }

        if (isDecRot) {
            std::vector<int> revNums = nums;
            std::reverse(revNums.begin(), revNums.end());
            int rZeroIdx = -1;
            for (int i = 0; i < n; ++i) {
                if (revNums[i] == 0) {
                    rZeroIdx = i;
                    break;
                }
            }
            ans = std::min(ans, 1 + rZeroIdx);
            ans = std::min(ans, nMinus1Idx + 1);
        }

        return ans > n * 2 ? -1 : ans;
    }
};