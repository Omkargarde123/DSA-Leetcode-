#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> exact(n + 1, 0);
        vector<int> one(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            exact[i] = exact[i + 1];

            int j = m - 1 - exact[i];

            if (j >= 0 && word1[i] == word2[j])
                exact[i]++;

            one[i] = one[i + 1];

            j = m - 1 - one[i];

            if (j >= 0 && word1[i] == word2[j])
                one[i] = max(one[i], one[i + 1] + 1);

            int cnt = exact[i + 1];
            j = m - 1 - cnt;

            if (j >= 0 && word1[i] != word2[j])
                one[i] = max(one[i], cnt + 1);
        }

        vector<int> ans;
        int p = 0;
        bool changed = false;

        for (int i = 0; i < m; ++i) {
            int remaining = m - i - 1;

            while (p < n) {
                if (word1[p] == word2[i]) {
                    if (one[p + 1] >= remaining) {
                        ans.push_back(p);
                        p++;
                        break;
                    }
                } else if (!changed) {
                    if (exact[p + 1] >= remaining) {
                        ans.push_back(p);
                        p++;
                        changed = true;
                        break;
                    }
                }

                p++;
            }

            if (p == n && ans.size() != i + 1)
                return {};
        }

        return ans;
    }
};