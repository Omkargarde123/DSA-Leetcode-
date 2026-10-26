class Solution {
private:
    long long dfs(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        int m = grid.size();
        int n = grid[0].size();
        
        visited[r][c] = true;
        long long current_sum = grid[r][c];
        
        // 4-directional offsets: up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && grid[nr][nc] > 0) {
                current_sum += dfs(nr, nc, grid, visited);
            }
        }
        
        return current_sum;
    }

public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long total_value = dfs(i, j, grid, visited);
                    if (total_value % k == 0) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};