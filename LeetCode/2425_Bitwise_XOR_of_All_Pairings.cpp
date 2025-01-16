/*
 * Author: Sagar Karatagi
 * Date: 16th January 2025
 * 
 * Description:
 * This solution calculates the XOR of all possible pairs between two vectors, `nums1` and `nums2`. 
 * The optimization leverages the property of XOR and the fact that elements contribute 
 * to the final XOR result only if the size of the other array is odd.
 * 
 * Functionality:
 * - If the size of `nums2` is odd, each element in `nums1` will contribute to the result.
 * - Similarly, if the size of `nums1` is odd, each element in `nums2` will contribute to the result.
 */

class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int result = 0; // Initialize result to store the cumulative XOR.

        // If the size of nums2 is odd, XOR all elements of nums1 with the result.
        if (nums2.size() % 2 == 1) {
            for (const int& num : nums1) {
                result ^= num; // XOR each element of nums1 into result.
            }
        }

        // If the size of nums1 is odd, XOR all elements of nums2 with the result.
        if (nums1.size() % 2 == 1) {
            for (const int& num : nums2) {
                result ^= num; // XOR each element of nums2 into result.
            }
        }

        return result; // Return the final XOR result.
    }
};
