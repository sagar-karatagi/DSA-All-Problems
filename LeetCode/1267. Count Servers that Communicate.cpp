/**
 * @file CountServers.cpp
 * @author Sagar Karatagi
 * @date 2025-01-23
 * @brief Solution to the "Count Servers that Communicate" problem.
 *
 * This program calculates the number of servers in a grid that can communicate 
 * with at least one other server. Two servers can communicate if they are in 
 * the same row or the same column.
 */

#include <vector>
using namespace std;

class Solution {
public:
    /**
     * @brief Counts the servers in the grid that can communicate.
     * 
     * The method first counts the number of servers in each row and column, 
     * then determines if a server can communicate based on those counts.
     * 
     * @param grid A 2D vector representing the grid, where 1 indicates a server 
     *             and 0 indicates an empty cell.
     * @return The number of servers that can communicate.
     */
    int countServers(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        vector<int> rowCount(rows, 0), colCount(cols, 0);

        // Step 1: Count servers in each row and column
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        // Step 2: Count servers that can communicate
        int ans = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // A server can communicate if its row or column has more than one server
                if (grid[i][j] == 1 && (rowCount[i] > 1 || colCount[j] > 1)) {
                    ans++;
                }
            }
        }

        return ans;
    }
};
