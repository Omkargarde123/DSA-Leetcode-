class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minIdx = 0, maxIdx = 0;
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] < nums[minIdx]) minIdx = i;
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }
        
        int i = min(minIdx, maxIdx);
        int j = max(minIdx, maxIdx);
        
        int option1 = j + 1;               // Delete both from front
        int option2 = n - i;               // Delete both from back
        int option3 = (i + 1) + (n - j);   // Delete one from front, one from back
        
        return min({option1, option2, option3});
    }
};