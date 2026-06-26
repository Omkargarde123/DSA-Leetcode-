
class Solution {
private:
    int limit;
    std::vector<int> bit;

    void update(int idx, int delta) {
        while (idx <= limit) {
            bit[idx] += delta;
            idx += idx & (-idx);
        }
    }

    long long query(int idx) {
        long long sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }

public:
    long long countMajoritySubarrays(std::vector<int>& nums, int target) {
        if (std::find(nums.begin(), nums.end(), target) == nums.end()) {
            return 0;
        }

        int n = nums.size();
        std::vector<int> pref(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            int val = (nums[i] == target) ? 1 : -1;
            pref[i + 1] = pref[i] + val;
        }

        std::vector<int> unique_vals = pref;
        std::sort(unique_vals.begin(), unique_vals.end());
        unique_vals.erase(std::unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());

        limit = unique_vals.size();
        bit.assign(limit + 1, 0);

        long long total_subarrays = 0;

        for (int p_val : pref) {
            int rank = std::lower_bound(unique_vals.begin(), unique_vals.end(), p_val) - unique_vals.begin() + 1;
            total_subarrays += query(rank - 1);
            update(rank, 1);
        }

        return total_subarrays;
    }
};