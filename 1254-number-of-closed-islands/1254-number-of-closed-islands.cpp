#include <vector>

class Solution {
private:
    void dfs(int r, int c, std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == 1) {
            return;
        }
        
        grid[r][c] = 1;
        
        dfs(r + 1, c, grid);
        dfs(r - 1, c, grid);
        dfs(r, c + 1, grid);
        dfs(r, c - 1, grid);
    }

public:
    int closedIsland(std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && grid[r][c] == 0) {
                    dfs(r, c, grid);
                }
            }
        }
        
        int closedIslandsCount = 0;
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                if (grid[r][c] == 0) {
                    closedIslandsCount++;
                    dfs(r, c, grid); 
                }
            }
        }
        
        return closedIslandsCount;
    }
};