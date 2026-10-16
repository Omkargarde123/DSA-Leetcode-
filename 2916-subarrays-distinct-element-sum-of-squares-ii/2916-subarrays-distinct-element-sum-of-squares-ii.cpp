class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        long long MOD = 1e9 + 7;
        
        unordered_map<int, int> last_pos;
        
        vector<long long> tree(4 * n, 0);
        vector<long long> sum_val(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto apply = [&](int node, int l, int r, long long val) {
            tree[node] = (tree[node] + 2 * val * sum_val[node] % MOD + val * val % MOD * (r - l + 1)) % MOD;
            sum_val[node] = (sum_val[node] + val * (r - l + 1)) % MOD;
            lazy[node] = (lazy[node] + val) % MOD;
        };

        auto push = [&](int node, int l, int r) {
            if (lazy[node] != 0) {
                int mid = l + (r - l) / 2;
                apply(2 * node, l, mid, lazy[node]);
                apply(2 * node + 1, mid + 1, r, lazy[node]);
                lazy[node] = 0;
            }
        };

        auto update = [&](auto& self, int node, int l, int r, int ql, int qr, long long val) -> void {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                apply(node, l, r, val);
                return;
            }
            push(node, l, r);
            int mid = l + (r - l) / 2;
            self(self, 2 * node, l, mid, ql, qr, val);
            self(self, 2 * node + 1, mid + 1, r, ql, qr, val);
            tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
            sum_val[node] = (sum_val[2 * node] + sum_val[2 * node + 1]) % MOD;
        };

        long long total_sum = 0;

        for (int j = 0; j < n; ++j) {
            int p = -1;
            if (last_pos.find(nums[j]) != last_pos.end()) {
                p = last_pos[nums[j]];
            }
            
            update(update, 1, 0, n - 1, p + 1, j, 1);
            last_pos[nums[j]] = j;
            
            total_sum = (total_sum + tree[1]) % MOD;
        }

        return total_sum;
    }
};