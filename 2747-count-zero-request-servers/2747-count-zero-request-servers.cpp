#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    std::vector<int> countServers(int n, std::vector<std::vector<int>>& logs, int x, std::vector<int>& queries) {
        int m = queries.size();
        std::vector<int> ans(m, 0);
        
        std::vector<std::pair<int, int>> sorted_queries(m);
        for (int i = 0; i < m; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        std::sort(sorted_queries.begin(), sorted_queries.end());
        
        std::vector<std::pair<int, int>> sorted_logs(logs.size());
        for (size_t i = 0; i < logs.size(); ++i) {
            sorted_logs[i] = {logs[i][1], logs[i][0]};
        }
        std::sort(sorted_logs.begin(), sorted_logs.end());
        
        int l = 0, r = 0;
        int active_servers = 0;
        std::unordered_map<int, int> server_counts;
        
        for (int i = 0; i < m; ++i) {
            int q_time = sorted_queries[i].first;
            int q_idx = sorted_queries[i].second;
            
            int window_start = q_time - x;
            int window_end = q_time;
            
            while (r < sorted_logs.size() && sorted_logs[r].first <= window_end) {
                int server_id = sorted_logs[r].second;
                if (server_counts[server_id] == 0) {
                    active_servers++;
                }
                server_counts[server_id]++;
                r++;
            }
            
            while (l < r && sorted_logs[l].first < window_start) {
                int server_id = sorted_logs[l].second;
                server_counts[server_id]--;
                if (server_counts[server_id] == 0) {
                    active_servers--;
                }
                l++;
            }
            
            ans[q_idx] = n - active_servers;
        }
        
        return ans;
    }
};