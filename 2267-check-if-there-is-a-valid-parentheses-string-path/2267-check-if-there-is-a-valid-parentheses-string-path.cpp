#include <vector>

using namespace std;

class Solution {
    int m, n;
    bool visited[100][100][200];

    bool dfs(int r, int c, int balance, vector<vector<char>>& grid) {
        // Increment/decrement balance based on current character
        balance += (grid[r][c] == '(' ? 1 : -1);

        // If balance drops below 0, parentheses sequence is invalid
        if (balance < 0) return false;

        // Base case: reached bottom-right cell
        if (r == m - 1 && c == n - 1) {
            return balance == 0;
        }

        // If this state has already been visited, skip it
        if (visited[r][c][balance]) return false;
        visited[r][c][balance] = true;

        // Move right
        if (c + 1 < n && dfs(r, c + 1, balance, grid)) {
            return true;
        }
        // Move down
        if (r + 1 < m && dfs(r + 1, c, balance, grid)) {
            return true;
        }

        return false;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // 1. Path length must be even to form valid matching pairs
        if ((m + n - 1) % 2 != 0) return false;

        // 2. Must start with '(' and end with ')'
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

        return dfs(0, 0, 0, grid);
    }
};