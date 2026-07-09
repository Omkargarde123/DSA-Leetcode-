#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;

        vector<int> digits;
        vector<int> orig_idx;
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                digits.push_back(s[i] - '0');
                orig_idx.push_back(i);
            }
        }

        int n = digits.size();
        if (n == 0) {
            return vector<int>(queries.size(), 0);
        }

        vector<long long> pref_sum(n + 1, 0);
        vector<long long> pref_val(n + 1, 0);
        vector<long long> pow10(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            pref_sum[i + 1] = pref_sum[i] + digits[i];
            pref_val[i + 1] = (pref_val[i] * 10 + digits[i]) % MOD;
            pow10[i + 1] = (pow10[i] * 10) % MOD;
        }

        vector<int> next_nonzero(m, -1);
        vector<int> prev_nonzero(m, -1);

        int last = -1;
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') last = i;
            prev_nonzero[i] = last;
        }

        int first = -1;
        for (int i = m - 1; i >= 0; --i) {
            if (s[i] != '0') first = i;
            next_nonzero[i] = first;
        }

        auto get_compressed_idx = [&](int original_idx) {
            return lower_bound(orig_idx.begin(), orig_idx.end(), original_idx) - orig_idx.begin();
        };

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            int first_nz = next_nonzero[l];
            int last_nz = prev_nonzero[r];

            if (first_nz == -1 || last_nz == -1 || first_nz > last_nz) {
                answer.push_back(0);
                continue;
            }

            int L = get_compressed_idx(first_nz);
            int R = get_compressed_idx(last_nz);

            long long current_sum = pref_sum[R + 1] - pref_sum[L];
            long long x = (pref_val[R + 1] - (pref_val[L] * pow10[R - L + 1]) % MOD + MOD) % MOD;

            long long res = (x * (current_sum % MOD)) % MOD;
            answer.push_back(res);
        }

        return answer;
    }
};