class Solution {
public:
    int distinctSubseqII(string s) {
        int MOD = 1e9 + 7;
        vector<long long> last(26, 0);

        for (char c : s) {
            long long total = 1; // 1 for the sequence containing only character c itself
            for (int i = 0; i < 26; ++i) {
                total = (total + last[i]) % MOD;
            }
            last[c - 'a'] = total;
        }

        long long ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans = (ans + last[i]) % MOD;
        }

        return ans;
    }
};