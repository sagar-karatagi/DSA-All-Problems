/*
 * Problem: Number of Laser Beams in a Bank
 * Source: LeetCode (Problem 2125)
 * 
 * Description:
 * Each string in the vector 's' represents a row in a bank security layout.
 * A '1' in a string represents a security device, and a '0' represents an empty cell.
 * A laser beam connects devices from two different rows if both rows contain at least one device,
 * and there are no rows with devices between them.
 * 
 * The task is to count the total number of such beams.
 * 
 * Approach:
 * - For each row, count the number of active devices (i.e., number of '1's).
 * - Maintain the count of devices in the previous non-empty row (`prev`).
 * - If the current row has at least one device (`curr > 0`), 
 *   then the number of beams between this row and the previous one is `curr * prev`.
 * - Accumulate the result in `ans` and update `prev` to the current row's count.
 * - Rows with zero devices are skipped since they don’t contribute to beams.
 * 
 * Time Complexity: O(n * m)
 * - n: number of rows
 * - m: number of columns in each row
 * 
 * Space Complexity: O(1)
 * - Uses only a few integer variables for counting.
 */

class Solution {
public:
    int numberOfBeams(vector<string>& s) {
        int prev = 0;  // Number of devices in the previous non-empty row
        int ans = 0;   // Total number of laser beams
        int n = s.size();
        int m = s[0].size();

        for (int i = 0; i < n; i++) {
            int curr = 0;
            // Count number of devices ('1') in the current row
            for (int j = 0; j < m; j++) {
                curr += (s[i][j] == '1');
            }

            // If the current row has devices, calculate beams
            if (curr > 0) {
                ans += curr * prev;
                prev = curr; // Update previous non-empty row device count
            }
        }

        return ans;
    }
};
