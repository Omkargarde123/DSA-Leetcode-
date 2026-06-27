

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> counts;
        for (int num : nums) {
            counts[num]++;
        }

        int maxLength = 0;

      
        if (counts.count(1)) {
            int countOne = counts[1];
            
            if (countOne % 2 == 0) {
                maxLength = max(maxLength, countOne - 1);
            } else {
                maxLength = max(maxLength, countOne);
            }
        }

        
        for (auto& [num, count] : counts) {
            if (num == 1) continue;

            long long current = num;
            int currentLength = 0;

            while (counts.count(current) && counts[current] >= 2) {
                currentLength += 2;
                current = current * current; 
            }

          
            if (counts.count(current) && counts[current] >= 1) {
                currentLength += 1;
            } else {
               
                currentLength -= 1;
            }

            maxLength = max(maxLength, currentLength);
        }

        return maxLength;
    }
};