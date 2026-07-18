class Solution {
    public int findGCD(int[] nums) {
        int min = nums[0];
        int max = nums[0];
        
        // Find the minimum and maximum values in one pass
        for (int num : nums) {
            if (num < min) min = num;
            if (num > max) max = num;
        }
        
        // Calculate the GCD using the Euclidean algorithm
        return gcd(min, max);
    }
    
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}