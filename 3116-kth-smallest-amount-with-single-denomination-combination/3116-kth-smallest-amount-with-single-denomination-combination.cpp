#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    long long gcd(long long a, long long b) {
        return std::gcd(a, b);
    }

    long long lcm(long long a, long long b) {
        return (a / gcd(a, b)) * b;
    }

    // Returns the number of distinct amounts <= x that can be formed
    long long countAmounts(long long x, const std::vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        // Iterate through all non-empty subsets using bitmask
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long current_lcm = 1;
            int set_bits = 0;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    set_bits++;
                    current_lcm = lcm(current_lcm, coins[i]);
                    if (current_lcm > x) break; // Optimization: early exit
                }
            }

            if (set_bits % 2 == 1) {
                count += x / current_lcm;
            } else {
                count -= x / current_lcm;
            }
        }

        return count;
    }

    long long findKthSmallest(std::vector<int>& coins, int k) {
        long long low = 1;
        long long min_coin = *std::min_element(coins.begin(), coins.end());
        long long high = min_coin * (long long)k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (countAmounts(mid, coins) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid amount
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};