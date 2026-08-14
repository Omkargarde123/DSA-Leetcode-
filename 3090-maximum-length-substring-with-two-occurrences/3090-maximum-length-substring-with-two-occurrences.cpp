class Solution {
public:
    int maximumLengthSubstring(string s) {
        int i=0;
        int j=0;
        int ans=0;
       int n=s.size();
      unordered_map<char, int> mp;
        for(int i=0; i<n; i++){
            mp[s[i]]++;
            if(mp[s[i]]>2){
                while(mp[s[i]]>2){
                    mp[s[j]]--;
                    j++;
                }
            }
            ans=max(ans, i-j+1);
        }
        return ans;
        
    }
};