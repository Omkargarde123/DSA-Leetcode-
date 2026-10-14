#include <string>
#include <algorithm>
#include <iostream>

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // If the maximum possible sum with 'num' 9s is less than 'sum', or if 0 sum requires positive digits
        // Wait, a positive integer cannot start with 0 if it has multiple digits, but here sum >= 1.
        // Let's build the number greedily.
        std::string result = "";
        
        for (int i = 0; i < num; ++i) {
            int take = std::min(9, sum);
            result += std::to_string(take);
            sum -= take;
        }
        
        // If there is still remaining sum, it's impossible to form the number
        if (sum > 0) {
            return "";
        }
        
        return result;
    }
};