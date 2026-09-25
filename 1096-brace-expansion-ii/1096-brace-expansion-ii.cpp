#include <string>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
    // Helper to combine two sets via Cartesian product (Concatenation)
    set<string> combine(const set<string>& set1, const set<string>& set2) {
        set<string> res;
        for (const string& s1 : set1) {
            for (const string& s2 : set2) {
                res.insert(s1 + s2);
            }
        }
        return res;
    }

    // Helper to take union of two sets (Comma operation)
    set<string> unionSets(const set<string>& set1, const set<string>& set2) {
        set<string> res = set1;
        res.insert(set2.begin(), set2.end());
        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        stack<char> ops;
        stack<set<string>> operands;

        for (int i = 0; i < expression.length(); i++) {
            char c = expression[i];

            if (c == '{') {
                // If previous character could form a concatenation (letter or '}'), insert implicit '.'
                if (i > 0 && (isalpha(expression[i - 1]) || expression[i - 1] == '}')) {
                    while (!ops.empty() && ops.top() == '.') {
                        ops.pop();
                        auto right = operands.top(); operands.pop();
                        auto left = operands.top(); operands.pop();
                        operands.push(combine(left, right));
                    }
                    ops.push('.');
                }
                ops.push('{');
            } else if (c == ',') {
                // Process all operations until reaching the matching '{'
                while (!ops.empty() && ops.top() != '{') {
                    char op = ops.top(); ops.pop();
                    auto right = operands.top(); operands.pop();
                    auto left = operands.top(); operands.pop();
                    if (op == '.') {
                        operands.push(combine(left, right));
                    } else if (op == ',') {
                        operands.push(unionSets(left, right));
                    }
                }
                ops.push(',');
            } else if (c == '}') {
                // Process operations inside the current braces
                while (!ops.empty() && ops.top() != '{') {
                    char op = ops.top(); ops.pop();
                    auto right = operands.top(); operands.pop();
                    auto left = operands.top(); operands.pop();
                    if (op == '.') {
                        operands.push(combine(left, right));
                    } else if (op == ',') {
                        operands.push(unionSets(left, right));
                    }
                }
                ops.pop(); // Pop '{'
            } else { // Lowercase English letter
                // Check for implicit concatenation before pushing new single-letter set
                if (i > 0 && (isalpha(expression[i - 1]) || expression[i - 1] == '}')) {
                    while (!ops.empty() && ops.top() == '.') {
                        ops.pop();
                        auto right = operands.top(); operands.pop();
                        auto left = operands.top(); operands.pop();
                        operands.push(combine(left, right));
                    }
                    ops.push('.');
                }
                operands.push({string(1, c)});
            }
        }

        // Process remaining operators on stack
        while (!ops.empty()) {
            char op = ops.top(); ops.pop();
            auto right = operands.top(); operands.pop();
            auto left = operands.top(); operands.pop();
            if (op == '.') {
                operands.push(combine(left, right));
            } else if (op == ',') {
                operands.push(unionSets(left, right));
            }
        }

        set<string> resultSet = operands.top();
        return vector<string>(resultSet.begin(), resultSet.end());
    }
};