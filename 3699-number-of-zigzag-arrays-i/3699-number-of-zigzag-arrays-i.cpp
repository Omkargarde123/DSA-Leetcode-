#include <vector>
#include <numeric>

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        if (n == 1) return r - l + 1;
        
        long long MOD = 1e9 + 7;
        int m = r - l + 1;
        
        std::vector<long long> dp_down(m, 0);
        std::vector<long long> dp_up(m, 0);
        
        for (int x = 0; x < m; ++x) {
            dp_up[x] = x;            
            dp_down[x] = (m - 1) - x;
        }
        
        for (int i = 3; i <= n; ++i) {
            std::vector<long long> next_down(m, 0);
            std::vector<long long> next_up(m, 0);
            
            long long suffix_sum = 0;
            for (int y = m - 1; y >= 0; --y) {
                next_down[y] = suffix_sum % MOD;
                suffix_sum = (suffix_sum + dp_up[y]) % MOD;
            }
            
            long long prefix_sum = 0;
            for (int y = 0; y < m; ++y) {
                next_up[y] = prefix_sum % MOD;
                prefix_sum = (prefix_sum + dp_down[y]) % MOD;
            }
            
            dp_down = std::move(next_down);
            dp_up = std::move(next_up);
        }
        
        long long total_count = 0;
        for (int x = 0; x < m; ++x) {
            total_count = (total_count + dp_down[x] + dp_up[x]) % MOD;
        }
        
        return total_count;
    }
};