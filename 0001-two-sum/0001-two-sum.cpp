class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();

        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right < n; right++) {
                if (nums[left] + nums[right] == target) {
                    return {left, right};
                }
            }
        }

        return {};
    }
};