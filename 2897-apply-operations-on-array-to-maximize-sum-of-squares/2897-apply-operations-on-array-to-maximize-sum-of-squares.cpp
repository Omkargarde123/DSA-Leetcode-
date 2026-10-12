class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> bitCount(30, 0);

        // Count the frequency of each set bit across all numbers
        for (int x : nums) {
            for (int i = 0; i < 30; ++i) {
                if ((x >> i) & 1) {
                    bitCount[i]++;
                }
            }
        }

        long long totalSum = 0;
        long long MOD = 1e9 + 7;

        // Greedily construct the k largest possible numbers
        for (int step = 0; step < k; ++step) {
            long long currentVal = 0;
            for (int i = 0; i < 30; ++i) {
                if (bitCount[i] > 0) {
                    currentVal |= (1 << i);
                    bitCount[i]--;
                }
            }
            totalSum = (totalSum + (currentVal * currentVal) % MOD) % MOD;
        }

        return totalSum;
    }
};