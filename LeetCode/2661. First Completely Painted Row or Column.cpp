/**
 * @file Solution.cpp
 * @author Sagar Karatagi
 * @date 20-01-2025
 * 
 * @brief This file contains the implementation of the Solution class, which provides
the functionality to find the first complete index in a matrix where either a row
or a column becomes fully represented by elements of a given array.
 *
 * @details
 * The problem involves finding the earliest index in an array such that either
 * a complete row or a complete column of a given 2D matrix can be constructed
 * using the elements of the array up to that index. The solution leverages
 * efficient mapping and row/column-wise traversal to achieve the desired outcome.
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    unordered_map<int, int> mp; ///< Maps each element in the array to its index.

    /**
     * @brief Finds the minimum index required to complete a row in the matrix.
     * @param mat The 2D matrix.
     * @return The earliest index in the array where any row is fully represented.
     */
    int solveRow(vector<vector<int>>& mat) {
        int ans = INT_MAX;
        for (int i = 0; i < mat.size(); i++) {
            int index = -1;
            for (int j = 0; j < mat[0].size(); j++) {
                index = max(index, mp[mat[i][j]]);
            }
            ans = min(ans, index);
        }
        return ans;
    }

    /**
     * @brief Finds the minimum index required to complete a column in the matrix.
     * @param mat The 2D matrix.
     * @return The earliest index in the array where any column is fully represented.
     */
    int solveCol(vector<vector<int>>& mat) {
        int ans = INT_MAX;
        for (int j = 0; j < mat[0].size(); j++) {
            int index = -1;
            for (int i = 0; i < mat.size(); i++) {
                index = max(index, mp[mat[i][j]]);
            }
            ans = min(ans, index);
        }
        return ans;
    }

public:
    /**
     * @brief Finds the first complete index in the array.
     * @param arr The array representing the order of elements.
     * @param mat The 2D matrix.
     * @return The earliest index in the array where either a row or a column
     *         in the matrix is fully represented.
     * 
     * @details
     * The function first maps each element of the array to its index for quick lookup.
     * Then it calculates the minimum index for both rows and columns and returns the
     * smaller of the two values.
     */
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        // Map each element in the array to its index
        for (int i = 0; i < arr.size(); i++) {
            mp[arr[i]] = i;
        }

        // Find the minimum index for rows and columns
        return min(solveRow(mat), solveCol(mat));
    }
};
