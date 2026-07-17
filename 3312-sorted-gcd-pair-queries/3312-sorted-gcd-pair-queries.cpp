
class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = *max_element(nums.begin(), nums.end());
        
        
        vector<long long> count(max_val + 1, 0);
        for (int num : nums) {
            count[num]++;
        }
        
        vector<long long> gcd_count(max_val + 1, 0);
        
       
        for (int g = max_val; g >= 1; --g) {
            long long total_multiples = 0;
            for (int multiple = g; multiple <= max_val; multiple += g) {
                total_multiples += count[multiple];
            }
            
            long long total_pairs = total_multiples * (total_multiples - 1) / 2;
            
            
            for (int multiple = 2 * g; multiple <= max_val; multiple += g) {
                total_pairs -= gcd_count[multiple];
            }
            
            gcd_count[g] = total_pairs;
        }
      
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_count[i];
        }
        
      
        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            ans.push_back(distance(prefix_sums.begin(), it));
        }
        
        return ans;
    }
};