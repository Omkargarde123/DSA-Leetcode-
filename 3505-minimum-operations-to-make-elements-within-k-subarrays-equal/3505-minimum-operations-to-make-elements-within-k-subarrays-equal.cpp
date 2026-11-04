
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<long long> left, right;

        long long sumLeft = 0, sumRight = 0;

        vector<long long> cost(n - x + 1);

        // Balance the two multisets
        auto balance = [&]() {
            while (left.size() > right.size() + 1) {
                long long val = *left.rbegin();

                left.erase(prev(left.end()));
                sumLeft -= val;

                right.insert(val);
                sumRight += val;
            }

            while (left.size() < right.size()) {
                long long val = *right.begin();

                right.erase(right.begin());
                sumRight -= val;

                left.insert(val);
                sumLeft += val;
            }
        };

        // Insert an element
        auto add = [&](long long val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sumLeft += val;
            } else {
                right.insert(val);
                sumRight += val;
            }

            balance();
        };

        // Remove an element
        auto remove = [&](long long val) {
            auto it = left.find(val);

            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }

            balance();
        };

        // Calculate cost for first window
        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        for (int i = 0; i <= n - x; i++) {

            long long median = *left.rbegin();

            cost[i] =
                median * left.size() - sumLeft +
                sumRight - median * right.size();

            // Slide window
            if (i < n - x) {
                remove(nums[i]);
                add(nums[i + x]);
            }
        }

        // DP
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {

                // Skip current element
                dp[i][j] = dp[i - 1][j];

                // Select a window ending at i-1
                if (i >= x && dp[i - x][j - 1] != INF) {

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
