class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        int n = nums.size();
        
        if (n < 3) {
            return n;
        }
        
        int msb_index = 31 - __builtin_clz(n); 
        
        return 1 << (msb_index + 1);
    }
};