#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        // Base index to help calculate length of valid substring starting at index 0
        st.push(-1); 
        
        int maxLength = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    // Push current index as a new base boundary for valid substrings
                    st.push(i);
                } else {
                    // Calculate valid length: current index - index of last unmatched character
                    maxLength = std::max(maxLength, i - st.top());
                }
            }
        }
        
        return maxLength;
    }
};