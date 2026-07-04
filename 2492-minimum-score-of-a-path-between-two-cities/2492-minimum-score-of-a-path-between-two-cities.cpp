class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Build the adjacency list: node -> list of {neighbor, distance}
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int w = road[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        int min_score = INT_MAX;
        vector<bool> visited(n + 1, false);
        queue<int> q;

        // Start BFS from city 1
        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (const auto& edge : adj[curr]) {
                int neighbor = edge.first;
                int weight = edge.second;

                // Track the absolute minimum edge weight in this component
                min_score = min(min_score, weight);

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return min_score;
    }
};