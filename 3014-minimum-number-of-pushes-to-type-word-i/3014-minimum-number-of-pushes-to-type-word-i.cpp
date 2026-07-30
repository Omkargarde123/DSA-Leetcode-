class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int totalpushes = 0;

        for(int i=0; i<n; i++){
            totalpushes+= (i / 8) + 1;
        }

        return totalpushes;
        
    }
};