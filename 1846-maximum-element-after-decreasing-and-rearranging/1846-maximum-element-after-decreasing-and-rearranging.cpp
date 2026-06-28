class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        
        int current_max = 1;
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] > current_max) {
                current_max += 1;
            }
        }
        return current_max;
    }
};