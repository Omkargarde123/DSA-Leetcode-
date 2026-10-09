class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                open++;
            } else { // s[i] == ')'
                // Check if next character is also ')'
                if (i + 1 < n && s[i + 1] == ')') {
                    i++; // Consume the second ')'
                } else {
                    insertions++; // Insert missing second ')'
                }

                // Match the '))' pair with an open '('
                if (open > 0) {
                    open--;
                } else {
                    insertions++; // Insert missing '('
                }
            }
        }

        // Remaining unmatched '(' each need two ')'
        insertions += open * 2;

        return insertions;
    }
};