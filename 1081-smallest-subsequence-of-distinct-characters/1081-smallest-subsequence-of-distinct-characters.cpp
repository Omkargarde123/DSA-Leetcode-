

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> count(26, 0);
        vector<bool> in_stack(26, false);
        string result = "";
        
        for (char c : s) {
            count[c - 'a']++;
        }
        
        for (char c : s) {
            count[c - 'a']--;
            
            if (in_stack[c - 'a']) {
                continue;
            }
            
            while (!result.empty() && result.back() > c && count[result.back() - 'a'] > 0) {
                in_stack[result.back() - 'a'] = false;
                result.pop_back();
            }
            
            result.push_back(c);
            in_stack[c - 'a'] = true;
        }
        
        return result;
    }
};