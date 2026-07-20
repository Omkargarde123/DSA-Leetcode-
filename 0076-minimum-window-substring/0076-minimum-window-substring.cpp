class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> freq(128, 0);

        // Fill frequency of t
        for (char c : t) {
            freq[c]++;
        }

        int left = 0, right = 0;
        int count = t.size(); // total chars needed
        int minLen = INT_MAX, start = 0;

        while (right < s.size()) {
            // If this char is needed, decrease count
            if (freq[s[right]] > 0) {
                count--;
            }

            // Decrease freq (even if negative)
            freq[s[right]]--;
            right++;

            // When all characters matched
            while (count == 0) {
                // Update answer
                if (right - left < minLen) {
                    minLen = right - left;
                    start = left;
                }

                // Try to shrink
                freq[s[left]]++;

                if (freq[s[left]] > 0) {
                    count++; // we lost a needed char
                }

                left++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};