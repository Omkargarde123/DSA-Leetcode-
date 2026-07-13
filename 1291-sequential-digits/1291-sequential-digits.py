class Solution:
    def sequentialDigits(self, low: int, high: int) -> list[int]:
        digits = "123456789"
        result = []
        
        # Outer loop controls the length of the sequential number (from 2 to 9 digits)
        for length in range(2, 10):
            # Inner loop slides the window across the 'digits' string
            for start in range(10 - length):
                # Extract the substring and convert it to an integer
                num = int(digits[start : start + length])
                
                # Check if the generated number falls within the specified range
                if low <= num <= high:
                    result.append(num)
                # Optimization: if the number exceeds high, numbers of larger lengths will too
                elif num > high:
                    break
                    
        return result