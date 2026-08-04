class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int min_val = nums[0];
        int max_val = nums[0];
        unordered_set<int> present;

        for (int num : nums) {
            min_val = min(min_val, num);
            max_val = max(max_val, num);
            present.insert(num);
        }

        vector<int> missing;
        for (int i = min_val + 1; i < max_val; ++i) {
            if (present.find(i) == present.end()) {
                missing.push_back(i);
            }
        }

        return missing;
    }
};