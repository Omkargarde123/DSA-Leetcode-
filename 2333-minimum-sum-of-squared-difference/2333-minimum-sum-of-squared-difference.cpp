#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long totalOps = (long long)k1 + k2;
        
        vector<long long> count(100001, 0);
        long long maxDiff = 0;
        
        for (int i = 0; i < n; ++i) {
            int d = abs(nums1[i] - nums2[i]);
            if (d > 0) {
                count[d]++;
                maxDiff = max(maxDiff, (long long)d);
            }
        }
        
        for (long long d = maxDiff; d > 0 && totalOps > 0; --d) {
            if (count[d] > 0) {
                long long take = min(totalOps, count[d]);
                count[d] -= take;
                count[d - 1] += take;
                totalOps -= take;
            }
        }
        
        long long result = 0;
        for (long long d = 1; d <= 100000; ++d) {
            if (count[d] > 0) {
                result += count[d] * d * d;
            }
        }
        
        return result;
    }
};