#include <vector>
#include <queue>
#include <set>
#include <algorithm>

class Solution {
public:
    std::vector<int> busiestServers(int k, std::vector<int>& arrival, std::vector<int>& load) {
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> busy_servers;
        
        std::set<int> available_servers;
        for (int i = 0; i < k; ++i) {
            available_servers.insert(i);
        }

        std::vector<int> request_count(k, 0);
        int max_requests = 0;

        for (int i = 0; i < arrival.size(); ++i) {
            long long curr_time = arrival[i];
            
            while (!busy_servers.empty() && busy_servers.top().first <= curr_time) {
                available_servers.insert(busy_servers.top().second);
                busy_servers.pop();
            }

            if (available_servers.empty()) {
                continue;
            }

            int preferred_server = i % k;
            auto it = available_servers.lower_bound(preferred_server);

            if (it == available_servers.end()) {
                it = available_servers.begin();
            }

            int assigned_server = *it;
            available_servers.erase(it);

            long long free_time = curr_time + load[i];
            busy_servers.push({free_time, assigned_server});

            request_count[assigned_server]++;
            max_requests = std::max(max_requests, request_count[assigned_server]);
        }

        std::vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (request_count[i] == max_requests) {
                result.push_back(i);
            }
        }

        return result;
    }
};