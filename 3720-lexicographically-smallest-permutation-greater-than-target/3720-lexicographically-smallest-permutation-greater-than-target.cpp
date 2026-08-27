class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        int best_i = -1;
        char best_char = ' ';

       
        for (int i = 0; i < n; i++) {
           
            for (int c = target[i] - 'a' + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    best_i = i;
                    best_char = 'a' + c;
                    break; 
                }
            }

           
            int target_char = target[i] - 'a';
            if (freq[target_char] > 0) {
                freq[target_char]--;
            } else {
                break;
            }
        }

        
        if (best_i == -1) {
            return "";
        }

        
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a']++;
        }

        string ans = "";

       
        for (int i = 0; i < best_i; i++) {
            ans += target[i];
            counts[target[i] - 'a']--;
        }

        
        ans += best_char;
        counts[best_char - 'a']--;

       
        for (int c = 0; c < 26; c++) {
            while (counts[c] > 0) {
                ans += ('a' + c);
                counts[c]--;
            }
        }

        return ans;
    }
};