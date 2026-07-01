#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isValid(int r, int c, int n) {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        // If the start or destination cell contains a thief, safeness factor is immediately 0
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        // Step 1: Multi-source BFS to calculate the minimum Manhattan distance to any thief
        vector<vector<int>> distToThief(n, vector<int>(n, 1e9));
        queue<pair<int, int>> q;

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    distToThief[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (isValid(nr, nc, n) && distToThief[nr][nc] == 1e9) {
                    distToThief[nr][nc] = distToThief[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Modified Dijkstra's using a Max-Heap to maximize the minimum safeness value on the path
        // Elements in heap: {safeness_factor, {r, c}}
        priority_queue<pair<int, pair<int, int>>> maxHeap;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        maxHeap.push({distToThief[0][0], {0, 0}});
        visited[0][0] = true;

        while (!maxHeap.empty()) {
            auto [safeness, cell] = maxHeap.top();
            auto [r, c] = cell;
            maxHeap.pop();

            // Reached the bottom-right corner
            if (r == n - 1 && c == n - 1) {
                return safeness;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (isValid(nr, nc, n) && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    // The safeness of the path to (nr, nc) is bottlenecked by the minimum value seen so far
                    int nextSafeness = min(safeness, distToThief[nr][nc]);
                    maxHeap.push({nextSafeness, {nr, nc}});
                }
            }
        }

        return 0;
    }
};