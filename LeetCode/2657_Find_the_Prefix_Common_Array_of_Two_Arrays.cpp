// Author: Sagar Karatagi
// Date: 2025-01-14
// Description: Solution to find the prefix common array of two input arrays A and B.
// The prefix common array is calculated such that each element at index i of the result
// represents the count of common elements between the prefixes of A and B up to index i.


class Solution {
public:
    /**
     * Finds the prefix common array of two input arrays A and B.
     * 
     * @param A Vector of integers representing the first input array.
     * @param B Vector of integers representing the second input array.
     * @return Vector of integers representing the prefix common array.
     */
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        // Maps to keep track of elements seen in A and B
        unordered_map<int, bool> mpA, mpB;
        int size = A.size(); // Length of input arrays
        vector<int> ans(size, 0); // Result array initialized to 0
        int prev = 0; // Keeps track of the previous common count

        for (int i = 0; i < size; i++) {
            int curr = B[i]; // Current element from array B
            int curr1 = A[i]; // Current element from array A

            // Mark elements as seen in their respective maps
            mpA[curr1] = true;
            mpB[curr] = true;

            // Check for common elements and update the count accordingly
            if (mpA.find(curr) != mpA.end() && mpB.find(curr1) != mpB.end()) {
                // If both current elements are found in the other's map
                prev += (curr == curr1) ? 1 : 2;
            } else if (mpA.find(curr) != mpA.end() || mpB.find(curr1) != mpB.end()) {
                // If either current element is found in the other's map
                prev++;
            }

            ans[i] = prev; // Update the result array with the current count
        }

        return ans; // Return the prefix common array
    }
};
