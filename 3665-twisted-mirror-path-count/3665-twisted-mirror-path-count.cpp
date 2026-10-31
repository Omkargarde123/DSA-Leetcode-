#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long MOD = 1e9 + 7;

        vector<vector<vector<pair<int, int>>>> memo(m, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(2, {-2, -2})));

        auto get_jump = [&](auto& self, int r, int c, int dir) -> pair<int, int> {
            int nr = r + (dir == 1 ? 1 : 0);
            int nc = c + (dir == 0 ? 1 : 0);

            if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                return {-1, -1};
            }

            if (grid[nr][nc] == 0) {
                return {nr, nc};
            }

            int next_dir = 1 - dir;
            if (memo[nr][nc][next_dir] != pair<int, int>{-2, -2}) {
                return memo[nr][nc][next_dir];
            }

            return memo[nr][nc][next_dir] = self(self, nr, nc, next_dir);
        };

        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][j] == 0) continue;

                pair<int, int> jump_right = get_jump(get_jump, i, j, 0);
                if (jump_right.first != -1) {
                    dp[jump_right.first][jump_right.second] = (dp[jump_right.first][jump_right.second] + dp[i][j]) % MOD;
                }

                pair<int, int> jump_down = get_jump(get_jump, i, j, 1);
                if (jump_down.first != -1) {
                    dp[jump_down.first][jump_down.second] = (dp[jump_down.first][jump_down.second] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};