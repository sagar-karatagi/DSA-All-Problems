/*
Author : Sagar Karatagi
Date : 11-1-2025
*/


class Solution {
public:
    /**
     * Function to determine if a string can be rearranged into exactly k palindrome substrings.
     *
     * @param s The input string.
     * @param k The required number of palindromes.
     * @return True if the string can be rearranged into k palindromes, otherwise false.
     */
    bool canConstruct(string s, int k) {
        int size = s.size();

        // If k is greater than the size of the string, it's impossible to construct k palindromes.
        if (k > size)
            return false;

        // If k is equal to the size of the string, each character can form a single palindrome.
        if (k == size)
            return true;

        // Count the frequency of each character in the string.
        vector<int> characterArray(26, 0);
        for (const char& c : s) {
            characterArray[c - 'a']++;
        }

        // Count the number of characters with odd frequencies.
        int odds = 0;
        for (const int& freq : characterArray) {
            odds+=freq%2;
        }

        // To construct k palindromes, the number of odd-frequency characters must not exceed k.
        return (odds <= k);
    }
};
