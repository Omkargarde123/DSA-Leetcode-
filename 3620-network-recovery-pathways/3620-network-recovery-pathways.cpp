

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        vector<vector<pair<int, int>>> adj(n);
        int max_edge_cost = 0;
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
            max_edge_cost = max(max_edge_cost, cost);
        }

        auto check = [&](int mid) -> bool {
            vector<long long> min_cost(n, -1);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

            min_cost[0] = 0;
            pq.push({0, 0});

            while (!pq.empty()) {
                auto [curr_cost, u] = pq.top();
                pq.pop();

                if (curr_cost > min_cost[u]) continue;
                if (u == n - 1) return curr_cost <= k;

                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int edge_cost = neighbor.second;

                    if (edge_cost < mid) continue;
                    if (v != n - 1 && !online[v]) continue;

                    long long next_cost = curr_cost + edge_cost;
                    if (min_cost[v] == -1 || next_cost < min_cost[v]) {
                        min_cost[v] = next_cost;
                        pq.push({next_cost, v});
                    }
                }
            }
            return min_cost[n - 1] != -1 && min_cost[n - 1] <= k;
        };

        int low = 0, high = max_edge_cost;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};