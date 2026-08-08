#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // exact[i] = maximum suffix of word2 that can be
        // matched exactly using word1[i...n-1]
        vector<int> exact(n + 1, 0);

        // one[i] = maximum suffix of word2 that can be
        // matched using word1[i...n-1] with at most one mismatch
        vector<int> one(n + 1, 0);

        // Build suffix information from right to left
        for (int i = n - 1; i >= 0; --i) {

            // ---------- Exact matching ----------
            exact[i] = exact[i + 1];

            int j = m - 1 - exact[i];

            if (j >= 0 && word1[i] == word2[j]) {
                exact[i]++;
            }

            // ---------- At most one mismatch ----------
            one[i] = one[i + 1];

            // Case 1:
            // word1[i] matches the next required character exactly
            j = m - 1 - one[i];

            if (j >= 0 && word1[i] == word2[j]) {
                one[i] = max(one[i], one[i + 1] + 1);
            }

            // Case 2:
            // Use the one allowed mismatch at word1[i].
            // Everything after i must match exactly.
            int exactCount = exact[i + 1];
            j = m - 1 - exactCount;

            if (j >= 0 && word1[i] != word2[j]) {
                one[i] = max(one[i], exactCount + 1);
            }
        }

        vector<int> ans;

        int p = 0;
        bool changed = false;

        for (int i = 0; i < m; ++i) {

            int remaining = m - i - 1;

            while (p < n) {

                // Case 1: current character matches exactly
                if (word1[p] == word2[i]) {

                    // Remaining part may use the one mismatch
                    if (one[p + 1] >= remaining) {
                        ans.push_back(p);
                        p++;
                        break;
                    }
                }

                // Case 2: current character is the one mismatch
                else if (!changed) {

                    // After using mismatch now,
                    // everything remaining must match exactly.
                    if (exact[p + 1] >= remaining) {
                        ans.push_back(p);
                        p++;
                        changed = true;
                        break;
                    }
                }

                p++;
            }

            if (p == n && ans.size() != i + 1) {
                return {};
            }
        }

        return ans;
    }
};