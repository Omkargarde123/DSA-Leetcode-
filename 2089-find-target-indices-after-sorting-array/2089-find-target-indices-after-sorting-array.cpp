class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int count_less = 0;
        int count_target = 0;
        
        for (int num : nums) {
            if (num < target) {
                count_less++;
            } else if (num == target) {
                count_target++;
            }
        }
        
        vector<int> result;
        for (int i = 0; i < count_target; ++i) {
            result.push_back(count_less + i);
        }
        
        return result;
    }
};