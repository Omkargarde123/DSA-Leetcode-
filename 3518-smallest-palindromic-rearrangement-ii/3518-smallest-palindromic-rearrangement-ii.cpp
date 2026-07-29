class Solution {
private:
    // Helper to compute nCr capped at 'cap' in O(min(r, cap)) time and O(1) space
    long long nCr(int n, int r, long long cap) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r; // Take advantage of symmetry
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            // Use __int128 to prevent overflow during intermediate multiplication
            __int128 next_val = (__int128)res * (n - i + 1) / i;
            if (next_val >= cap) return cap;
            res = (long long)next_val;
        }
        return res;
    }

public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        int m = n / 2;
        
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        vector<int> cnt(26, 0);
        char mid = 0;
        for (int i = 0; i < 26; i++) {
            cnt[i] = freq[i] / 2;
            if (freq[i] % 2 != 0) {
                mid = 'a' + i;
            }
        }
        
        long long cap = k + 1;
        
        // Helper to compute multinomial combinations capped at (k + 1)
        auto get_ways = [&](const vector<int>& c_arr) -> int {
            int rem = 0;
            for (int x : c_arr) rem += x;
            long long ways = 1;
            for (int x : c_arr) {
                if (x > 0) {
                    ways = min(cap, ways * nCr(rem, x, cap));
                    rem -= x;
                }
            }
            return (int)ways;
        };
        
        // If total distinct permutations < k, return empty string
        if (get_ways(cnt) < k) return "";
        
        // Construct the lexicographically k-th smallest first half
        string half = "";
        for (int i = 0; i < m; i++) {
            for (int c = 0; c < 26; c++) {
                if (cnt[c] > 0) {
                    cnt[c]--;
                    int ways = get_ways(cnt);
                    if (k <= ways) {
                        half += (char)('a' + c);
                        break; // Fixed character at current position
                    } else {
                        k -= ways;
                        cnt[c]++; // Backtrack
                    }
                }
            }
        }
        
        // Mirror the half string to form the final palindrome
        string ans = half;
        if (n % 2 != 0) {
            ans += mid;
        }
        string rev = half;
        reverse(rev.begin(), rev.end());
        ans += rev;
        
        return ans;
    }
};