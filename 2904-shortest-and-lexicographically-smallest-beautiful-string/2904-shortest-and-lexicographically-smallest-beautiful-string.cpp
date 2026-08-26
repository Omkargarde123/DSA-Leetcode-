class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();
        string ans = "";
        int ones = 0;
        int left = 0;
        
        for (int right = 0; right < n; ++right) {
            if (s[right] == '1') {
                ones++;
            }
           
            while (ones == k) {
                while (s[left] == '0') {
                    left++;
                }
                
                string current = s.substr(left, right - left + 1);
              if (ans.empty() || current.length() < ans.length() || 
                   (current.length() == ans.length() && current < ans)) {
                    ans = current;
                }
                
                left++;
                ones--;
            }
        }
        
        return ans;
    }
};


