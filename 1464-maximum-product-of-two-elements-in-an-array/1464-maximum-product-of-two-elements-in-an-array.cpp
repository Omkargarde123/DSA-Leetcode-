class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int first = 0, second = 0;

        for (int x : nums) {
            if (x > first) {
                second = first;
                first = x;
            } else if (x > second) {
                second = x;
            }
        }

        return (first - 1) * (second - 1);
    }
};


// class Solution {
// public:
//     int maxProduct(vector<int>& nums) {
//         int maxp = 0;

//         for (int i = 0; i < nums.size(); i++) {
//             for (int j = i + 1; j < nums.size(); j++) {
//                 maxp = max(maxp, (nums[i] - 1) * (nums[j] - 1));
//             }
//         }

//         return maxp;
//     }
// };