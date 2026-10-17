class Solution {
private:
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        // Store pairs of {digit_sum, value} along with their original index
        vector<pair<pair<int, int>, int>> items(n);
        for (int i = 0; i < n; ++i) {
            items[i] = {{getDigitSum(nums[i]), nums[i]}, i};
        }
        
        // Sort based on digit sum first, then by value
        sort(items.begin(), items.end());
        
        // Find the minimum swaps required to sort the permutation
        vector<bool> visited(n, false);
        int swaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // If already visited or already in the correct position, skip
            if (visited[i] || items[i].second == i) {
                continue;
            }
            
            // Traverse the cycle
            int cycleSize = 0;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                curr = items[curr].second;
                cycleSize++;
            }
            
            if (cycleSize > 1) {
                swaps += (cycleSize - 1);
            }
        }
        
        return swaps;
    }
};