class Solution {
public:
    // KMP helper
    bool kmpSearch(vector<int>& text, vector<int>& pattern) {
        int n = text.size(), m = pattern.size();
        
        vector<int> lps(m, 0);
        
        // build LPS
        for (int i = 1, j = 0; i < m; ) {
            if (pattern[i] == pattern[j]) {
                lps[i++] = ++j;
            } else if (j > 0) {
                j = lps[j - 1];
            } else {
                lps[i++] = 0;
            }
        }
        
        // search
        for (int i = 0, j = 0; i < n; ) {
            if (text[i] == pattern[j]) {
                i++; j++;
                if (j == m) return true;
            } else if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
        
        return false;
    }
    
    bool isRotation(vector<int>& a, vector<int>& b) {
        vector<int> temp = a;
        temp.insert(temp.end(), a.begin(), a.end());
        return kmpSearch(temp, b);
    }
    
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        
        int sum = 0;
        
        // iterate only divisors
        for (int k = 1; k * k <= n; k++) {
            if (n % k != 0) continue;
            
            vector<int> divisors = {k};
            if (k != n / k) divisors.push_back(n / k);
            
            for (int d : divisors) {
                bool ok = true;
                
                for (int i = 0; i < n; i += d) {
                    vector<int> a(nums.begin() + i, nums.begin() + i + d);
                    vector<int> b(sorted.begin() + i, sorted.begin() + i + d);
                    
                    if (!isRotation(a, b)) {
                        ok = false;
                        break;
                    }
                }
                
                if (ok) sum += d;
            }
        }
        
        return sum;
    }
};