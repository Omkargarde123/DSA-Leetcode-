class Solution {
public:
    bool isValid(int i, int j, int n, int m, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
        return (i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '1' && !visited[i][j]);
    }

    void dfs(int i, int j, int n, int m, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
        if (!isValid(i, j, n, m, grid, visited)) {
            return;
        }

        visited[i][j] = true;

        dfs(i + 1, j, n, m, grid, visited); // Down
        dfs(i - 1, j, n, m, grid, visited); // Up
        dfs(i, j + 1, n, m, grid, visited); // Right
        dfs(i, j - 1, n, m, grid, visited); // Left
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int islandCount = 0;
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfs(i, j, n, m, grid, visited);
                    islandCount++;
                }
            }
        }

        return islandCount;
    }
};