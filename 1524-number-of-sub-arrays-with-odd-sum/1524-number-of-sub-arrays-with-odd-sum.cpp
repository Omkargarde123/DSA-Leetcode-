class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int MOD = 1e9 + 7;
        long long oddCount = 0;
        long long evenCount = 1;
        long long prefixSum = 0;
        long long totalSubarrays = 0;
        
        for (int num : arr) {
            prefixSum += num;
            if (prefixSum % 2 != 0) {
                totalSubarrays = (totalSubarrays + evenCount) % MOD;
                oddCount++;
            } else {
                totalSubarrays = (totalSubarrays + oddCount) % MOD;
                evenCount++;
            }
        }
        
        return totalSubarrays;
    }
};
