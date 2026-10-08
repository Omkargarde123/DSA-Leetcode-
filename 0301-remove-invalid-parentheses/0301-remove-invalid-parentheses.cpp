#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left_rem = 0, right_rem = 0;
        
        // Step 1: Calculate the minimum '(' and ')' to remove
        for (char c : s) {
            if (c == '(') {
                left_rem++;
            } else if (c == ')') {
                if (left_rem > 0) {
                    left_rem--;
                } else {
                    right_rem++;
                }
            }
        }

        unordered_set<string> result;
        string current = "";
        
        // Step 2: Backtrack to generate all valid combinations
        backtrack(s, 0, 0, 0, left_rem, right_rem, current, result);
        
        return vector<string>(result.begin(), result.end());
    }

private:
    void backtrack(const string& s, int index, int open_count, int close_count, 
                   int left_rem, int right_rem, string& current, unordered_set<string>& result) {
        if (index == s.length()) {
            if (left_rem == 0 && right_rem == 0) {
                result.insert(current);
            }
            return;
        }

        char c = s[index];

        // Choice 1: Remove current parenthesis (if budget permits)
        if (c == '(' && left_rem > 0) {
            backtrack(s, index + 1, open_count, close_count, left_rem - 1, right_rem, current, result);
        } else if (c == ')' && right_rem > 0) {
            backtrack(s, index + 1, open_count, close_count, left_rem, right_rem - 1, current, result);
        }

        // Choice 2: Keep current character
        current.push_back(c);

        if (c != '(' && c != ')') {
            // Keep letters
            backtrack(s, index + 1, open_count, close_count, left_rem, right_rem, current, result);
        } else if (c == '(') {
            // Keep '('
            backtrack(s, index + 1, open_count + 1, close_count, left_rem, right_rem, current, result);
        } else if (c == ')' && open_count > close_count) {
            // Keep ')' only if it balances an earlier '('
            backtrack(s, index + 1, open_count, close_count + 1, left_rem, right_rem, current, result);
        }

        // Backtrack state
        current.pop_back();
    }
};