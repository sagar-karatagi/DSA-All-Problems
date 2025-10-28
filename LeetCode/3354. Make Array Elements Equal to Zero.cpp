/**
 * LeetCode 3354. Make Array Elements Equal to Zero
 * 
 * Problem:
 * ----------
 * You are given an integer array `nums`.
 * 
 * Starting from a position `curr` where `nums[curr] == 0`, and choosing a direction (left or right),
 * we perform the following process repeatedly:
 * 
 * 1. If `curr` goes out of bounds [0, n - 1], the process ends.
 * 2. If `nums[curr] == 0`, move in the current direction (increment or decrement `curr`).
 * 3. If `nums[curr] > 0`:
 *      - Decrease `nums[curr]` by 1
 *      - Reverse the current direction
 *      - Move one step in the new direction
 * 
 * A starting configuration (index `curr`, and direction) is *valid* if by the end of the process,
 * all elements in `nums` become zero.
 * 
 * You must count how many valid selections exist.
 * 
 * -------------------------------------------------------------------------
 * Intuition and Observations:
 * -------------------------------------------------------------------------
 * Let's observe how the process works logically rather than simulating.
 * 
 * - Every time we move, the array changes direction whenever a nonzero element is encountered.
 * - For the array to be fully reducible to zeros, there must be a certain *balance* between
 *   elements on both sides of any starting zero.
 * 
 * If we take prefix sums (`pre[i]` = sum of first `i + 1` elements), then:
 * 
 * - Sum of elements to the *left* of index `i`:  `left = pre[i - 1]` (or 0 if i == 0)
 * - Sum of elements to the *right* of index `i`: `right = pre[n - 1] - pre[i]`
 * 
 * Now:
 * - If `left == right` and `nums[i] == 0`, it means that starting from this zero,
 *   you can move in *either* direction symmetrically and make all numbers zero → add `2`.
 * - If `|left - right| == 1` and `nums[i] == 0`, you can move only in *one* direction
 *   (the side that has one more element to balance) → add `1`.
 * 
 * -------------------------------------------------------------------------
 * Algorithm Steps:
 * -------------------------------------------------------------------------
 * 1. Compute the prefix sum array.
 * 2. For each index `i`:
 *      - Compute `left` and `right` sums.
 *      - If `nums[i] == 0`, check the above two conditions.
 * 3. Count total valid starting selections.
 * 
 * -------------------------------------------------------------------------
 * Example:
 * -------------------------------------------------------------------------
 * Input: nums = [1, 0, 2, 0, 3]
 * 
 * Prefix sums = [1, 1, 3, 3, 6]
 * 
 * At i = 1 (nums[i] = 0):
 *     left = 1, right = 5 → not equal, difference = 4 → invalid
 * 
 * At i = 3 (nums[i] = 0):
 *     left = 3, right = 3 → equal → valid → contributes 2
 * 
 * Output = 2
 * 
 * -------------------------------------------------------------------------
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * -------------------------------------------------------------------------
 */

class Solution {
    public int countValidSelections(int[] nums) {
        int n = nums.length;

        // Step 1: Compute prefix sum array
        int[] pre = new int[n];
        pre[0] = nums[0];
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i - 1] + nums[i];
        }

        int ans = 0;

        // Step 2: Check valid conditions for each zero position
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                int left = (i == 0 ? 0 : pre[i - 1]);
                int right = pre[n - 1] - pre[i];

                if (left == right) {
                    // Both directions are valid
                    ans += 2;
                } else if (Math.abs(left - right) == 1) {
                    // Only one direction is valid
                    ans += 1;
                }
            }
        }

        // Step 3: Return the number of valid selections
        return ans;
    }
}
