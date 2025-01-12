/**
 * @file ValidParenthesesChecker.cpp
 * @brief This program checks whether a given string of parentheses can be valid with flexible positions.
 *
 * @author Sagar Karatagi
 * @date 12-1-2025
 *
 * @details
 * - Input:
 *   - A string `s` containing only '(' and ')' characters.
 *   - A string `locked` of the same length as `s`, where:
 *     - `locked[i] == '1'` indicates the character at `s[i]` is fixed and cannot change.
 *     - `locked[i] == '0'` indicates the character at `s[i]` can be changed to either '(' or ')'.
 * - Output: Returns `true` if the string can be made valid; otherwise, returns `false`.
 * - A string is valid if:
 *   - It is empty, or it contains balanced parentheses.
 */


class Solution {
public:
    /**
     * @brief Determines if a string can be made valid by modifying flexible positions.
     *
     * @param s The input string containing only '(' and ')'.
     * @param locked A string indicating whether characters in `s` are locked ('1') or flexible ('0').
     * @return True if the string can be made valid, otherwise false.
     */
    bool canBeValid(string s, string locked) {
        if (s.size() % 2 != 0) {
            return false; // Odd-length strings can't be valid.
        }
        
        // Left-to-right pass
        int balance = 0;    // Tracks '(' count
        int flexible = 0;   // Tracks unlocked positions
        for (int i = 0; i < s.size(); i++) {
            if (locked[i] == '0') {
                flexible++; // Can act as either '(' or ')'
            } else if (s[i] == '(') {
                balance++;
            } else {
                balance--;
            }
            
            // Ensure flexibility can cover negative balances
            if (balance + flexible < 0) {
                return false;
            }
        }

        // Right-to-left pass
        balance = 0;
        flexible = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (locked[i] == '0') {
                flexible++; // Can act as either '(' or ')'
            } else if (s[i] == ')') {
                balance++;
            } else {
                balance--;
            }
            
            // Ensure flexibility can cover negative balances
            if (balance + flexible < 0) {
                return false;
            }
        }

        return true;
    }
};
