/**
 * @file Solution.cpp
 * 
 * @brief Implementation of the Edit Distance problem using memoization.
 * 
 * This solution provides an efficient recursive approach with memoization to compute the minimum edit distance between two strings.
 * 
 * The edit distance is calculated using three possible operations:
 * - Deletion
 * - Replacement
 * - Insertion
 * 
 * @version 1.0
 * @date 18-01-25
 * 
 * Author: Sagar Karatagi
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    /**
     * @brief Recursive function to solve the Edit Distance problem with memoization.
     * 
     * @param word1 First string.
     * @param word2 Second string.
     * @param i1 Current index in word1.
     * @param i2 Current index in word2.
     * @param dp Memoization table to store computed results.
     * @return int Minimum edit distance.
     */
    int solve(string& word1, string& word2, int i1, int i2, vector<vector<int>>& dp) {
        // Base cases
        if (i1 == word1.size()) {
            return word2.size() - i2; // Insert remaining characters of word2
        }
        if (i2 == word2.size()) {
            return word1.size() - i1; // Delete remaining characters of word1
        }

        // If already computed
        if (dp[i1][i2] != -1) {
            return dp[i1][i2];
        }

        if (word1[i1] == word2[i2]) {
            // Characters match, move both pointers
            return dp[i1][i2] = solve(word1, word2, i1 + 1, i2 + 1, dp);
        }

        // Operations: delete, replace, insert
        int del = 1 + solve(word1, word2, i1 + 1, i2, dp);
        int replace = 1 + solve(word1, word2, i1 + 1, i2 + 1, dp);
        int insert = 1 + solve(word1, word2, i1, i2 + 1, dp);

        // Return the minimum of all three operations
        return dp[i1][i2] = min({del, replace, insert});
    }

public:
    /**
     * @brief Function to find the minimum edit distance between two strings.
     * 
     * @param word1 First string.
     * @param word2 Second string.
     * @return int Minimum edit distance.
     */
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1)); // Memoization table
        return solve(word1, word2, 0, 0, dp);
    }
};

int main() {
    // Example usage
    Solution solution;
    string word1 = "horse";
    string word2 = "ros";
    cout << "Minimum Edit Distance: " << solution.minDistance(word1, word2) << endl;
    return 0;
}
