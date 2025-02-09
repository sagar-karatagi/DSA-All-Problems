/**
 * @brief Solution to count the number of bad pairs in an array.
 *
 * @details
 * This program computes the number of "bad pairs" in an array. A pair (i, j) 
 * is defined as "bad" if the condition `j - i != nums[j] - nums[i]` holds true. 
 * The algorithm uses an efficient approach based on hashing to count "good pairs" 
 * (where the condition doesn't hold) and subtracts this count from the total 
 * number of pairs to find the number of "bad pairs".
 *
 * The algorithm works in O(n) time complexity by leveraging an unordered_map 
 * to store the differences and efficiently count the occurrences of "good pairs".
 *
 * @author sagar-karatagi
 * @date 2025-02-09
 */

#include <unordered_map>
#include <vector>

class Solution {
public:
    /**
     * @brief Count the number of bad pairs in the array.
     * 
     * @param nums A vector of integers representing the input array.
     * @return The number of bad pairs in the array.
     * 
     * @timecomplexity O(n) - The algorithm iterates through the array once, 
     *                         and all operations with the hash map are O(1) on average.
     * @spacecomplexity O(n) - Space is used for the hash map to store up to n unique entries.
     */
    long long countBadPairs(std::vector<int>& nums) {
        // Hash map to store the frequency of differences (i - nums[i])
        std::unordered_map<int, int> mp;
        
        // Total number of elements in the array
        int n = nums.size();
        
        // Total number of pairs in the array
        long long total = (long long)n * (n - 1) / 2;
        
        // Variable to count the number of "good pairs"
        long long goodPairs = 0;

        // Iterate over the array to calculate good pairs
        for (int i = 0; i < n; i++) {
            // Increment goodPairs by the count of occurrences of (i - nums[i])
            goodPairs += mp[i - nums[i]];
            
            // Update the frequency of (i - nums[i]) in the hash map
            mp[i - nums[i]]++;
        }

        // Total bad pairs = total pairs - good pairs
        return total - goodPairs;
    }
};
