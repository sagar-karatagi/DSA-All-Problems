/*
 * ProductOfNumbers
 *
 * This class implements a system that allows adding numbers sequentially
 * and efficiently calculating the product of the last `k` numbers using a prefix product approach.
 *
 * Author: sagar-karatagi
 * Date: 2025-02-14
 */

#include <vector>
using namespace std;

class ProductOfNumbers {
private:
    vector<int> pre{1}; // Prefix product array initialized with 1

public:
    /**
     * Constructor
     * Initializes the ProductOfNumbers object.
     */
    ProductOfNumbers() {}

    /**
     * Adds a number to the sequence.
     * @param num The number to be added.
     *        - If the number is 0, the prefix product is reset.
     *        - Otherwise, the number is multiplied with the last prefix product and added to the vector.
     */
    void add(int num) {
        if (num != 0) {
            pre.push_back(num * pre.back()); // Multiply with the last prefix product
        } else {
            pre.clear();                   // Reset prefix product on zero
            pre.push_back(1);              // Add 1 as the base case
        }
    }

    /**
     * Returns the product of the last `k` numbers.
     * @param k The number of elements to include in the product.
     * @return The product of the last `k` numbers, or 0 if the sequence was reset within the last `k` numbers.
     *
     * Explanation:
     * - If `k` is greater than the current size of the prefix product array, the product is 0.
     * - Otherwise, the result is calculated using division: pre.back() / pre[pre.size() - k - 1].
     */
    int getProduct(int k) {
        return k < pre.size() ? pre.back() / pre[pre.size() - k - 1] : 0;
    }
};


