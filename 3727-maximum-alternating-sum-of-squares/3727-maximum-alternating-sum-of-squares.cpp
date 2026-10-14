class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        // Transform each number to its squared value
        vector<long long> squares(n);
        for (int i = 0; i < n; ++i) {
            long long val = nums[i];
            squares[i] = val * val;
        }
        
        // Sort the squared values in ascending order
        sort(squares.begin(), squares.end());
        
        long long maxScore = 0;
        int mid = n / 2;
        
        // Subtract the smaller half
        for (int i = 0; i < mid; ++i) {
            maxScore -= squares[i];
        }
        
        // Add the larger half
        for (int i = mid; i < n; ++i) {
            maxScore += squares[i];
        }
        
        return maxScore;
    }
};