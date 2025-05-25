// Accepted
// 120 / 120 testcases passed
// Time taken: 6 m 35 s
// Sagar Karatagi
// Submitted at May 25, 2025 08:59

// Solution
// Runtime: 31 ms — Beats 81.69%
// Memory: 171.90 MB — Beats 73.05%

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> mp;

        // Count the frequency of each word
        for (const string& word : words) {
            mp[word]++;
        }

        int ans = 0;
        bool has_center = false;

        for (auto& [word, count] : mp) {
            string rev = word;
            reverse(rev.begin(), rev.end());

            if (word == rev) {
                // If the word is palindromic (like "aa", "cc")
                // Use as many full pairs as possible (each pair = 4 chars)
                int pairs = count / 2;
                ans += pairs * 4;

                // If one word is left unused, it can go in the center
                if (count % 2 == 1) {
                    has_center = true;
                }
            } else if (word < rev && mp.count(rev)) {
                // If word is not palindromic, find its reverse (like "ab" and "ba")
                // To avoid double-counting, process only when word < rev lexicographically
                int pairs = min(count, mp[rev]);
                ans += pairs * 4;
            }
        }

        // If there's an unused palindromic word, place it in the center (adds 2 chars)
        if (has_center) ans += 2;

        return ans;
    }
};
