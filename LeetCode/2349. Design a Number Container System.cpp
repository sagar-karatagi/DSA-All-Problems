/**
 * @author sagar karatagi
 * @date 8-2-2025
 * @brief A C++ implementation of a data structure that allows storing numbers at indices 
 *        and querying the smallest index for a specific number. The implementation uses 
 *        two hash maps and a priority queue for efficient operations.
 */

#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>

class NumberContainers {
    /**
     * @brief Maps a number to a priority queue of indices where it appears.
     *        The priority queue is a min-heap, ensuring the smallest index is at the top.
     */
    std::unordered_map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> numToindex;

    /**
     * @brief Maps an index to the number stored at that index.
     */
    std::unordered_map<int, int> indexToNum;

public:
    /**
     * @brief Constructor for the NumberContainers class.
     *        Initializes the I/O settings for faster input/output operations.
     */
    NumberContainers() {
        ios::sync_with_stdio(false); // Disable synchronization with C I/O streams for faster performance
        cin.tie(nullptr);            // Untie cin from cout for faster input
        cout.tie(nullptr);           // Untie cout from cin for faster output
    }

    /**
     * @brief Changes the number at a specific index. If the index already has a number, it is replaced.
     * 
     * @param index The index to update.
     * @param number The new number to store at the index.
     */
    void change(int index, int number) {
        // Update the index-to-number mapping
        indexToNum[index] = number;

        // Push the index into the min-heap corresponding to the number
        numToindex[number].push(index);
    }

    /**
     * @brief Finds the smallest index where a specific number is stored.
     * 
     * @param number The number to search for.
     * @return The smallest index where the number is stored, or -1 if the number is not found.
     */
    int find(int number) {
        // Check if the number exists in the map
        if (numToindex.find(number) == numToindex.end()) return -1;

        // Remove any outdated indices from the min-heap
        while (!numToindex[number].empty() && 
               indexToNum[numToindex[number].top()] != number) {
            numToindex[number].pop();
        }

        // If the min-heap is empty after cleanup, the number does not exist
        return numToindex[number].empty() ? -1 : numToindex[number].top();
    }
};

/**
 * @example
 * NumberContainers nc;
 * nc.change(1, 10);    // Store 10 at index 1
 * nc.change(2, 10);    // Store 10 at index 2
 * int result = nc.find(10); // Returns 1 (smallest index with number 10)
 * nc.change(1, 20);    // Replace 10 with 20 at index 1
 * result = nc.find(10); // Returns 2 (smallest index with number 10 now)
 */
