class Solution {
public:
    int memo[101][101];

    int solve(int i, int m, const vector<int>& suffixSum, int n) {
        // Base case: if remaining piles are <= 2 * m, take all remaining piles
        if (i + 2 * m >= n) {
            return suffixSum[i];
        }

        if (memo[i][m] != -1) {
            return memo[i][m];
        }

        int maxStones = 0;

        // Try taking X piles (1 <= X <= 2 * m)
        for (int x = 1; x <= 2 * m; ++x) {
            int nextM = max(m, x);
            // Current player gets remaining sum minus what the opponent will optimaly get
            int currentStones = suffixSum[i] - solve(i + x, nextM, suffixSum, n);
            maxStones = max(maxStones, currentStones);
        }

        return memo[i][m] = maxStones;
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffixSum(n);
        
        // Compute suffix sums from right to left
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // Initialize memoization table
        fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(int), -1);

        return solve(0, 1, suffixSum, n);
    }
};