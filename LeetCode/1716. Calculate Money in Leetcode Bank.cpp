/*
Author : Sagar Karatagi 
───────────────────────────────────────────────────────────────────────────────
🏦 Leetcode 1716 — Calculate Money in Leetcode Bank
───────────────────────────────────────────────────────────────────────────────

🧩 Problem Statement:
─────────────────────
Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.

- On the first Monday, he deposits $1.
- From Tuesday to Sunday, he deposits $1 more than the previous day.
- Every next Monday, he deposits $1 more than the previous Monday.

Given an integer `n`, return the total amount of money Hercy will have in the bank 
at the end of the n-th day.

───────────────────────────────────────────────────────────────────────────────
📘 Examples:

Example 1:
Input:  n = 4
Output: 10
Explanation: Deposits → [1, 2, 3, 4] → Total = 10

Example 2:
Input:  n = 10
Output: 37
Explanation: Week1 → [1, 2, 3, 4, 5, 6, 7]
             Week2 → [2, 3, 4]
             Total = 37

Example 3:
Input:  n = 20
Output: 96
Explanation: 
Week1 → [1, 2, 3, 4, 5, 6, 7]
Week2 → [2, 3, 4, 5, 6, 7, 8]
Week3 → [3, 4, 5, 6, 7, 8]
Total = 96

───────────────────────────────────────────────────────────────────────────────
🧠 Intuition:
─────────────
The pattern forms arithmetic progressions (AP):

- Each week (Monday → Sunday) is an AP:
    first term (a) = week number
    difference (d) = 1
    number of terms (n) = 7

- The remaining days (if any) form another AP starting from (weeks + 1).

Hence we can compute directly using the sum of AP formula instead of looping.

───────────────────────────────────────────────────────────────────────────────
📐 Mathematical Derivation:
───────────────────────────

AP Sum Formula:
    S = n/2 * (2a + (n - 1)d)

Let:
    w = n / 7   → number of complete weeks
    r = n % 7   → remaining days

1️⃣ Sum for complete weeks:
    For week i (1-indexed): a = i, n = 7, d = 1
    S_i = 7/2 * (2i + 6) = 7i + 21

    Therefore, total for all full weeks:
        S_weeks = Σ(7i + 21) for i=1 to w
                 = 7 * (w(w + 1) / 2) + 21w [1] 

2️⃣ Sum for remaining days:
    a = w + 1, n = r, d = 1
    S_rem = r/2 * (2(w + 1) + (r - 1))
           = r(w + 1) + r(r - 1)/2

3️⃣ Total:
    Total = S_weeks + S_rem
           = 7 * (w(w + 1)) / 2 + 21w + r(w + 1) + r(r - 1)/2

───────────────────────────────────────────────────────────────────────────────
💻 Implementation (C++):
────────────────────────
*/

class Solution {
public:
    int totalMoney(int n) {
        int w = n / 7; // Number of complete weeks
        int r = n % 7; // Remaining days in the last (incomplete) week

        // Sum of all complete weeks using AP sum formula
        int total = (7 * w * (w + 1)) / 2 + 21 * w;

        // Sum of the remaining days using AP sum formula
        total += r * (w + 1) + (r * (r - 1)) / 2;

        return total;
    }
};

/*
───────────────────────────────────────────────────────────────────────────────
⏱️ Complexity Analysis:
──────────────────────────────
Time Complexity:  O(1)  → Only uses direct formulas
Space Complexity: O(1)  → No extra memory used

📚 Tags:
──────────────────────────────
Math • Simulation • Arithmetic Progression • Implementation
───────────────────────────────────────────────────────────────────────────────
[1] We have used the formula sum(n) = (n(n+1))/2 in total calc as i = 1 to w 
*/
