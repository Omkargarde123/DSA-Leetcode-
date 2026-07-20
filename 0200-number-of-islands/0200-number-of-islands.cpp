

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int rows = grid.size();
        int cols = grid[0].size();
        int islandCount = 0;
        
        // Direction vectors for moving up, down, left, and ri6ght
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                // If we find an unvisited piece of land ('1')
                if (grid[r][c] == '1') {
                    islandCount++; // Found a new island
                    
                    // Start BFS to sink the entire island
                    queue<pair<int, int>> q;
                    q.push({r, c});
                    grid[r][c] = '0'; // Mark as visited by changing '1' to '0'
                    
                    while (!q.empty()) {
                        auto [currRow, currCol] = q.front();
                        q.pop();
                        
                        // Check all 4 neighboring directions
                        for (int i = 0; i < 4; i++) {
                            int nRow = currRow + dRow[i];
                            int nCol = currCol + dCol[i];
                            
                            // If the neighbor is valid land, push to queue and mark visited
                            if (nRow >= 0 && nRow < rows && nCol >= 0 && nCol < cols && grid[nRow][nCol] == '1') {
                                q.push({nRow, nCol});
                                grid[nRow][nCol] = '0'; 
                            }
                        }
                    }
                }
            }
        }
        
        return islandCount;
    }
};