/**
 * @file MinimumTimeToMakeRopeColorful.cpp
 * @author [Your Name]
 * @brief Solution for LeetCode Problem 1578 - Minimum Time to Make Rope Colorful
 * @version 1.0
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 *
 * Problem:
 * --------
 * Alice has n balloons arranged on a rope. Each balloon has a color and
 * a time required to remove it. We need to ensure that no two consecutive
 * balloons have the same color by removing the minimum total removal time.
 *
 * Approach:
 * ----------
 * - We iterate through the string of colors.
 * - For every group of consecutive balloons with the same color:
 *      - We calculate the total removal time of that group.
 *      - We keep the balloon with the maximum removal time (since removing others costs less).
 *      - The cost for this group = (sum of all times) - (maximum time).
 * - The sum of all such costs across all groups gives the minimum total removal time.
 *
 * Example:
 * --------
 * colors = "aabaa", neededTime = [1,2,3,4,1]
 * Groups:
 *   "aa" (indices 0,1) -> sum = 3, max = 2 -> cost = 1
 *   "aa" (indices 3,4) -> sum = 5, max = 4 -> cost = 1
 * Total cost = 1 + 1 = 2
 *
 * Complexity:
 * ------------
 * Time Complexity:  O(n)  — single pass through the array.
 * Space Complexity: O(1)  — constant extra space.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int i = 0, totalCost = 0;

        while (i + 1 < n) {
            char currentColor = colors[i];
            int groupSum = 0;       // total removal time for current color group
            int maxTime = 0;        // max removal time in current color group

            // Process the entire group of same-colored balloons
            while (i < n && colors[i] == currentColor) {
                groupSum += neededTime[i];
                maxTime = max(maxTime, neededTime[i]);
                ++i;
            }

            // Remove all except the one with maximum time
            totalCost += (groupSum - maxTime);
        }

        return totalCost;
    }
};
