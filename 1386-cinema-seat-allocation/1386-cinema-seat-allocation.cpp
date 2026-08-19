class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rowMasks;
        
        // Group reservations by row using bitwise representation
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9) {
                rowMasks[row] |= (1 << (col - 2)); // Bit 0-7 represents seats 2-9
            }
        }
        
        // Default max groups if all rows were completely empty
        int maxGroups = n * 2;
        
        for (const auto& [row, mask] : rowMasks) {
            // Subtract 2 since this row has reservations, then add back possible allocations
            maxGroups -= 2;
            
            bool leftPossible = (mask & 0b00001111) == 0;   // Seats 2, 3, 4, 5
            bool rightPossible = (mask & 0b11110000) == 0;  // Seats 6, 7, 8, 9
            bool midPossible = (mask & 0b00111100) == 0;    // Seats 4, 5, 6, 7
            
            if (leftPossible && rightPossible) {
                maxGroups += 2;
            } else if (leftPossible || rightPossible || midPossible) {
                maxGroups += 1;
            }
        }
        
        return maxGroups;
    }
};