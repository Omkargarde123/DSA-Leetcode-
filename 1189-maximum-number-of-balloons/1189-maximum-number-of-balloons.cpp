
class Solution {
public:
    int maxNumberOfBalloons(std::string text) {
        
        int counts[26] = {0};
        
        
        for (char c : text) {
            counts[c - 'a']++;
        }
        
      
        int b = counts['b' - 'a'];
        int a = counts['a' - 'a'];
        int l = counts['l' - 'a'] / 2; 
        int o = counts['o' - 'a'] / 2; 
        int n = counts['n' - 'a'];
        
     
        return std::min({b, a, l, o, n});
    }
};