// minimum number of pushes to type word |


// class Solution {
// public:
//     int minimumPushes(string word) {
//         int n = word.length();
//         int pushes=0;

//         for (int i=0; i<n; i++){
//             pushes+=(i / 8) +1;
//         }

//         return pushes;
        
//     }
// };

class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }

        sort(freq.rbegin(), freq.rend());

        int totalPushes = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) break; 
            int pushesPerChar = (i / 8) + 1; 
            totalPushes += freq[i] * pushesPerChar;
        }

        return totalPushes;
    }
};