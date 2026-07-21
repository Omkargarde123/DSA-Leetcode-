class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }
        
        vector<pair<char, int>> blocks;
        for (char c : s) {
            if (blocks.empty() || blocks.back().first != c) {
                blocks.push_back({c, 1});
            } else {
                blocks.back().second++;
            }
        }
        
        int max_delta = 0;
        
        for (int i = 1; i < (int)blocks.size() - 1; ++i) {
            if (blocks[i].first == '1') {
                int left_zeros = blocks[i - 1].second;
                int right_zeros = blocks[i + 1].second;
                max_delta = max(max_delta, left_zeros + right_zeros);
            }
        }
        
        return total_ones + max_delta;
    }
};