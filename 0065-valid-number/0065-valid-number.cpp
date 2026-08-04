class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExponent = false;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];

            if (isdigit(c)) {
                seenDigit = true;
            } 
            else if (c == '+' || c == '-') {
                // A sign is valid only at the start or immediately after an 'e' / 'E'
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } 
            else if (c == '.') {
                // A dot cannot appear more than once or after an exponent
                if (seenDot || seenExponent) {
                    return false;
                }
                seenDot = true;
            } 
            else if (c == 'e' || c == 'E') {
                // 'e' / 'E' cannot appear more than once and must be preceded by a digit
                if (seenExponent || !seenDigit) {
                    return false;
                }
                seenExponent = true;
                seenDigit = false; // Reset to ensure digits exist after 'e' / 'E'
            } 
            else {
                // Any other invalid character (letters, symbols, spaces)
                return false;
            }
        }

        // Must end with at least one digit seen (handles trailing e/E or standalone signs/dots)
        return seenDigit;
    }
};