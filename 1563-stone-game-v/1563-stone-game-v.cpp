// DP PROBLEM 
// DIVIDE THE PROBLEM INTO THE SUB PROBLEM 
// AND ALSO THAT PROBLEM DIVIDE IN THE SUB PROBLEM
// AND CYCLLE IS GOES ON 
// WHEN 1 STONE REMAIING IN THE ARRAY 
// THEN STOP THE ITERATION AND 
// RETURN THE MAXIMUM SCORE 

// TIME COMPLEXITY = O(n*n)

// SPACE COMPLEXITY = O(n)

// FOR THE MEMIRY EXCEED WE HAVE TO SOLVE IN THIS COMPLEXITY 


class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;

                for (int k = l; k < r; k++) {
                    long long left = prefix[k + 1] - prefix[l];
                    long long right = prefix[r + 1] - prefix[k + 1];

                    if (left < right) {
                        dp[l][r] = max(dp[l][r],
                                       (int)left + dp[l][k]);
                    }
                    else if (left > right) {
                        dp[l][r] = max(dp[l][r],
                                       (int)right + dp[k + 1][r]);
                    }
                    else {
                        dp[l][r] = max(dp[l][r],
                                       (int)left + max(dp[l][k],
                                                      dp[k + 1][r]));
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};