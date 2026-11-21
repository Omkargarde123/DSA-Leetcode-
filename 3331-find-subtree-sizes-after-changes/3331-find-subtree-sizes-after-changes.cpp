#include <vector>
#include <string>
#include <array>

using namespace std;

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = static_cast<int>(parent.size());
        vector<vector<int>> origAdj(n);
        for (int i = 1; i < n; ++i) {
            origAdj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        array<int, 26> lastSeen;
        lastSeen.fill(-1);

        // Pass 1: Determine new parent for each node using original ancestors
        auto dfsFindParents = [&](auto& self, int u) -> void {
            int ch = s[u] - 'a';
            if (lastSeen[ch] != -1) {
                newParent[u] = lastSeen[ch];
            }

            int prev = lastSeen[ch];
            lastSeen[ch] = u;

            for (int v : origAdj[u]) {
                self(self, v);
            }

            lastSeen[ch] = prev;
        };

        dfsFindParents(dfsFindParents, 0);

        // Build final tree adjacency list
        vector<vector<int>> finalAdj(n);
        for (int i = 1; i < n; ++i) {
            finalAdj[newParent[i]].push_back(i);
        }

        // Pass 2: Compute subtree sizes in the final tree
        vector<int> ans(n, 1);
        auto dfsSubtreeSize = [&](auto& self, int u) -> int {
            int size = 1;
            for (int v : finalAdj[u]) {
                size += self(self, v);
            }
            return ans[u] = size;
        };

        dfsSubtreeSize(dfsSubtreeSize, 0);
        return ans;
    }
};