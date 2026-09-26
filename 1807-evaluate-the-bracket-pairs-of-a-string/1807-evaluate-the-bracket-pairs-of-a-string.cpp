#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // Build a hash map for O(1) lookup of keys
        unordered_map<string, string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }

        string result = "";
        string key = "";
        bool inBracket = false;

        for (char c : s) {
            if (c == '(') {
                inBracket = true;
                key.clear();
            } else if (c == ')') {
                inBracket = false;
                if (dict.count(key)) {
                    result += dict[key];
                } else {
                    result += '?';
                }
            } else {
                if (inBracket) {
                    key += c;
                } else {
                    result += c;
                }
            }
        }

        return result;
    }
};