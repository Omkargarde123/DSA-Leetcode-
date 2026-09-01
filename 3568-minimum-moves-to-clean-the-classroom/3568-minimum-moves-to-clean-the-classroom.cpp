class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        map<pair<int, int>, int> litter_map;
        int litter_count = 0;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    start_r = r;
                    start_c = c;
                } else if (classroom[r][c] == 'L') {
                    litter_map[{r, c}] = litter_count++;
                }
            }
        }

        int full_mask = (1 << litter_count) - 1;
        if (full_mask == 0) return 0; 

        vector<vector<vector<int>>> best_energy(m, vector<vector<int>>(n, vector<int>(1 << litter_count, -1)));

        queue<tuple<int, int, int, int, int>> q;
        q.push({start_r, start_c, 0, energy, 0});
        best_energy[start_r][start_c][0] = energy;

        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [r, c, mask, e, steps] = q.front();
            q.pop();

            if (mask == full_mask) return steps;
            if (e == 0) continue; 

            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                    int next_e = e - 1;
                    int next_mask = mask;

                    char cell = classroom[nr][nc];
                    if (cell == 'L') {
                        next_mask |= (1 << litter_map[{nr, nc}]);
                    } else if (cell == 'R') {
                        next_e = energy; 
                    }

                    if (next_e > best_energy[nr][nc][next_mask]) {
                        best_energy[nr][nc][next_mask] = next_e;
                        q.push({nr, nc, next_mask, next_e, steps + 1});
                    }
                }
            }
        }

        return -1;
    }
};