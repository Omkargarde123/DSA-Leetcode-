#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Pair each number with its original index and sort by value
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());

        vector<int> sorted_vals(n);
        vector<int> pos_in_sorted(n);
        for (int i = 0; i < n; ++i) {
            sorted_vals[i] = sorted_nodes[i].first;
            pos_in_sorted[sorted_nodes[i].second] = i;
        }

        // Initialize sparse table for binary lifting
        int LOG = 18; // 2^17 = 131072 > 10^5
        vector<vector<int>> up(n, vector<int>(LOG, 0));

        // Base case: 1 jump (2^0) to the furthest reachable node to the right
        for (int i = 0; i < n; ++i) {
            int val = sorted_vals[i];
            // Find the furthest index we can jump to within maxDiff
            auto it = upper_bound(sorted_vals.begin(), sorted_vals.end(), val + maxDiff);
            int target_idx = distance(sorted_vals.begin(), it) - 1;
            up[i][0] = target_idx;
        }

        // Fill the binary lifting table
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                if (up[i][0] == i) {
                    up[i][j] = i;
                } else {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }

        vector<int> ans;
        for (const auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int pos_u = pos_in_sorted[u];
            int pos_v = pos_in_sorted[v];

            // Always jump from smaller sorted index to the larger sorted index
            if (pos_u > pos_v) {
                swap(pos_u, pos_v);
            }

            int val_u = sorted_vals[pos_u];
            int val_v = sorted_vals[pos_v];

            // If they have identical values but different original indices, it takes exactly 1 jump
            if (val_u == val_v) {
                ans.push_back(1);
                continue;
            }

            // If the start node can't make any forward progress and cannot bridge the gap
            if (up[pos_u][0] == pos_u && val_v - val_u > maxDiff) {
                ans.push_back(-1);
                continue;
            }

            int steps = 0;
            int curr = pos_u;

            // Lift up to the node right before reaching or passing val_v
            for (int j = LOG - 1; j >= 0; --j) {
                int nxt = up[curr][j];
                if (sorted_vals[nxt] < val_v && nxt != curr) {
                    curr = nxt;
                    steps += (1 << j);
                }
            }

            // Take the final step to cross or hit val_v
            if (sorted_vals[curr] < val_v) {
                curr = up[curr][0];
                steps += 1;
            }

            // Verify if the landing node safely covers our destination index
            if (sorted_vals[curr] >= val_v && (curr >= pos_v || sorted_vals[curr] - val_v <= maxDiff)) {
                ans.push_back(steps);
            } else {
                ans.push_back(-1);
            }
        }

        return ans;
    }
};