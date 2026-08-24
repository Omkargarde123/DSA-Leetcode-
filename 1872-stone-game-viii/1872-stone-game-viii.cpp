class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<long long> pref(n);
        pref[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + stones[i];
        }
        long long ans = pref[n - 1];
        for (int i = n - 2; i >= 1; --i) {
            ans = max(ans, pref[i] - ans);
        }
        return ans;
    }
};