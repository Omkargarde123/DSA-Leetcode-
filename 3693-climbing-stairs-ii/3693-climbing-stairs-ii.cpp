class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<long long> dp(n + 1, -1);
        dp[0] = 0;
        
        for (int j = 1; j <= n; ++j) {
            long long min_cost = -1;
            
            for (int i = max(0, j - 3); i < j; ++i) {
                long long current_cost = dp[i] + costs[j - 1] + (long long)(j - i) * (j - i);
                
                if (min_cost == -1 || current_cost < min_cost) {
                    min_cost = current_cost;
                }
            }
            dp[j] = min_cost;
        }
        
        return dp[n];
    }
};