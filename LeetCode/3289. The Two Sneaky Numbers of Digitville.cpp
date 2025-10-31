/**
 * @file getSneakyNumbers.cpp
 * @brief Solution to LeetCode Problem 3289 - "The Two Sneaky Numbers of Digitville"
 * 
 * Problem Summary:
 * ----------------
 * In the town of Digitville, there is a list `nums` containing all integers from `0` to `n - 1`.
 * However, two numbers appear twice, making the list length `n + 2`.
 * 
 * The task is to find those two duplicated ("sneaky") numbers.
 * 
 * Example:
 * --------
 * Input:  nums = [0, 3, 2, 1, 3, 2]
 * Output: [2, 3]
 * 
 * Constraints:
 * ------------
 * - 2 <= n <= 100
 * - nums.length == n + 2
 * - 0 <= nums[i] < n
 * - Exactly two numbers appear twice
 * 
 * Approach:
 * ----------
 * This solution uses bitwise XOR operations to identify the two repeated numbers efficiently
 * in O(n) time and O(1) space.
 * 
 * Algorithm Steps:
 * ----------------
 * 1. XOR all numbers in `nums` and all numbers in the range [0, n-1].
 *    - Since all numbers except the repeated ones appear twice, all other pairs cancel out.
 *    - The result is y = a ^ b, where `a` and `b` are the two sneaky numbers.
 * 
 * 2. Find the lowest bit where `a` and `b` differ:
 *      int lowBit = y & -y;
 *    - This isolates the rightmost set bit in `y` (the bit that differs between `a` and `b`).
 * 
 * 3. Partition all numbers into two groups based on this bit:
 *      - Group 1: numbers where (num & lowBit) == 0
 *      - Group 2: numbers where (num & lowBit) != 0
 *    - `a` and `b` will end up in different groups.
 * 
 * 4. XOR each group separately.
 *    - All non-repeated numbers will cancel within their groups.
 *    - Only `a` and `b` remain.
 * 
 * 5. Return {a, b}.
 * 
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 * 
 * Author: <Your Name>
 * Date: <Upload Date>
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        int len = nums.size();
        int n = len - 2; // Original range is [0, n)

        // Step 1: XOR all numbers in nums and in [0, n)
        int y = 0;
        for (int num : nums)
            y ^= num;
        for (int i = 0; i < n; i++)
            y ^= i;

        // Step 2: Find the lowest bit where the two numbers differ
        int lowBit = y & -y;

        // Step 3: Partition numbers into two groups and XOR separately
        int a = 0, b = 0;
        for (int num : nums) {
            if (num & lowBit)
                a ^= num;
            else
                b ^= num;
        }
        for (int i = 0; i < n; i++) {
            if (i & lowBit)
                a ^= i;
            else
                b ^= i;
        }

        // Step 4: Return the two sneaky numbers
        return {a, b};
    }
};
