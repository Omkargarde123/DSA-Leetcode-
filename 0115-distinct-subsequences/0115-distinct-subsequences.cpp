class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[j] stores the number of subsequences of s that match t[0...j-1]
        vector<unsigned int> dp(n + 1, 0);
        
        // Base case: empty t can be formed in 1 way
        dp[0] = 1; 
        
        for (int i = 1; i <= m; ++i) {
            // Traverse backwards to use values from the previous iteration of i
            for (int j = n; j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        return dp[n];
    }
};