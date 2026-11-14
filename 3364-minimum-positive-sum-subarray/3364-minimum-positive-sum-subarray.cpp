class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int min_sum = INT_MAX;
        int n = nums.size();
        
        for (int len = l; len <= r; ++len) {
            int current_sum = 0;
            for (int i = 0; i < len; ++i) {
                current_sum += nums[i];
            }
            
            if (current_sum > 0) {
                min_sum = min(min_sum, current_sum);
            }
            
            for (int i = len; i < n; ++i) {
                current_sum += nums[i] - nums[i - len];
                if (current_sum > 0) {
                    min_sum = min(min_sum, current_sum);
                }
            }
        }
        
        return (min_sum == INT_MAX) ? -1 : min_sum;
    }
};