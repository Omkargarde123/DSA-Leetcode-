#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int subsequencePairCount(std::vector<int>& nums) {
        int MOD = 1e9 + 7;
        int max_val = 0;
        for (int x : nums) {
            max_val = std::max(max_val, x);
        }

        // dp[g1][g2] stores the number of pairs of subsequences with gcd g1 and g2
        // 0 represents an empty subsequence
        std::vector<std::vector<int>> dp(max_val + 1, std::vector<int>(max_val + 1, 0));
        dp[0][0] = 1; // Base case: both subsequences are empty

        for (int x : nums) {
            std::vector<std::vector<int>> next_dp = dp;

            for (int g1 = 0; g1 <= max_val; ++g1) {
                for (int g2 = 0; g2 <= max_val; ++g2) {
                    if (dp[g1][g2] == 0) continue;

                    // Option 1: Add x to the first subsequence
                    int ng1 = (g1 == 0) ? x : std::gcd(g1, x);
                    next_dp[ng1][g2] = (next_dp[ng1][g2] + dp[g1][g2]) % MOD;

                    // Option 2: Add x to the second subsequence
                    int ng2 = (g2 == 0) ? x : std::gcd(g2, x);
                    next_dp[g1][ng2] = (next_dp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }
            dp = std::move(next_dp);
        }

        long long ans = 0;
        // Sum up all states where g1 == g2 and neither is empty (g1 > 0)
        for (int g = 1; g <= max_val; ++g) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};