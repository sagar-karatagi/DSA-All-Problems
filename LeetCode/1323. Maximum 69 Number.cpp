class Solution {
public:
    int maximum69Number (int num) {
        int divisor = 1e4;
        while(divisor){
            int digit = (num/divisor)%10;
            if(digit == 6 ){
                num+= 3*divisor;
                break;
            }
            divisor/=10;
        }
        return num;
    }
};
