/**
 * Author: Sagar Karatagi
 * Date: 2025-01-15
 * 
 * Problem: Minimize XOR
 * Description: Given two integers num1 and num2, this function minimizes the XOR value 
 *              of num1 and another number x such that x has the same number of set bits 
 *              as num2.
 */

class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int bitCount = __builtin_popcount(num2); // Count the number of set bits in num2
        int x = 0;
        int i = 31;

        // First loop: Try to match set bits from num1
        while (i > -1 && bitCount > 0) {
            if (num1 & (1 << i)) {
                x |= (1 << i); // Set this bit in x
                bitCount--;    // Decrement the count of set bits to match
            }
            i--;
        }

        // Second loop: If bitCount > 0, fill the remaining set bits
        i = 0;
        while (bitCount > 0 && i < 32) {
            if ((x & (1 << i)) == 0) { // Only set bits in places where x does not have any
                x |= (1 << i);
                bitCount--;
            }
            i++;
        }
        return x;
    }
};
