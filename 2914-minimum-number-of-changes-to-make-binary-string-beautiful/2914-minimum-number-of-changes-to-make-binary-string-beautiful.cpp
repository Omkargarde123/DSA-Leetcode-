class Solution {
public:
    int minChanges(string s) {
        int changes = 0;
        for (int i = 0; i < static_cast<int>(s.size()); i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }
        return changes;
    }
};