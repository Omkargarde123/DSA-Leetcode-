// // bascally its graph based problem 
// // like we have to understand first the problem in such a way that
//                     |
//   Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
//                 |
                
//                 0 --> 1
//                 |     |
//                 2 --> 3

// GRAPH   


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // Build adjacency list and calculate indegrees
        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prerequisite = pre[1];
            adj[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        // Push all courses with 0 indegree into the queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);
            
            // Reduce in-degree for all neighbors
            for (int neighbor : adj[curr]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // If the ordering contains all courses, return it; otherwise, a cycle exists
        if (order.size() == numCourses) {
            return order;
        }
        
        return {};
    }
};