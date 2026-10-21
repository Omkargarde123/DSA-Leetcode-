#include <string>
#include <algorithm>

class Solution {
public:
    int minOperations(string s) {
        int n = s.length();
        if (n <= 1) return 0;

        bool sorted = true;
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] > s[i + 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;

        if (n == 2) return -1;

        char mn = s[0], mx = s[0];
        for (char c : s) {
            mn = min(mn, c);
            mx = max(mx, c);
        }

        bool mn_at_first = (s[0] == mn);
        bool mx_at_last = (s[n - 1] == mx);

        if (mn_at_first || mx_at_last) {
            return 1;
        }

        bool unique_max_first = (s[0] == mx);
        bool unique_min_last = (s[n - 1] == mn);

        for (int i = 1; i < n; ++i) {
            if (s[i] == mx) unique_max_first = false;
        }
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == mn) unique_min_last = false;
        }

        if (unique_max_first && unique_min_last) {
            return 3;
        }

        return 2;
    }
};