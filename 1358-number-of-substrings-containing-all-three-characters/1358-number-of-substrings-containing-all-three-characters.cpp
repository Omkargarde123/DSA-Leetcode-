class Solution {
public:
    int numberOfSubstrings(string s) {
        // Store the last seen positions of 'a', 'b', and 'c'
        int lastPos[3] = {-1, -1, -1};
        int count = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            // Update the last seen position of the current character
            lastPos[s[right] - 'a'] = right;
            
            // If all three characters have been seen at least once
            if (lastPos[0] != -1 && lastPos[1] != -1 && lastPos[2] != -1) {
                // The number of valid substrings ending at 'right' is 
                // determined by the minimum index among the three characters.
                count += min({lastPos[0], lastPos[1], lastPos[2]}) + 1;
            }
        }
        
        return count;
    }
};