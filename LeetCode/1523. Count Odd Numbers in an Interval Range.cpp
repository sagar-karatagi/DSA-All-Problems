//Author : Sagar Karatagi 
//Date : 7-12-25
class Solution {
public:
    int countOdds(int low, int high) {
        low = low - (low&1);
        high = high + (high&1);
        return (high-low)/2;
    }
};
