class Solution:
    def countMajoritySubarrays(self, nums: list[int], target: int) -> int:
        n = len(nums)
        ans = 0
        
        # Check all possible subarrays starting at index i
        for i in range(n):
            balance = 0
            for j in range(i, n):
                if nums[j] == target:
                    balance += 1
                else:
                    balance -= 1
                
                # If balance > 0, target is the majority element
                if balance > 0:
                    ans += 1
                    
        return ans