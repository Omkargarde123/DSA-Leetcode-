class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;
        
        // Normalize k
        k = k % total;
        
        // Initialize the result grid with the same dimensions
        vector<vector<int>> ans(m, vector<int>(n));
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                // Find the flattened 1D index
                int old_1d = r * n + c;
                
                // Find the new flattened 1D index after shifting
                int new_1d = (old_1d + k) % total;
                
                // Convert the new 1D index back to 2D coordinates
                int new_r = new_1d / n;
                int new_c = new_1d % n;
                
                ans[new_r][new_c] = grid[r][c];
            }
        }
        
        return ans;
    }
};