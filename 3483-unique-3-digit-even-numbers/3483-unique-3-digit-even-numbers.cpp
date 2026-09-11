class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> freq(10, 0);
        for (int d : digits) {
            freq[d]++;
        }

        int count = 0;

        for (int num = 100; num <= 998; num += 2) {
            int d1 = num / 100;       
            int d2 = (num / 10) % 10; 
            int d3 = num % 10;        

            vector<int> current_freq(10, 0);
            current_freq[d1]++;
            current_freq[d2]++;
            current_freq[d3]++;

            if (current_freq[d1] <= freq[d1] && 
                current_freq[d2] <= freq[d2] && 
                current_freq[d3] <= freq[d3]) {
                count++;
            }
        }

        return count;
    }
};