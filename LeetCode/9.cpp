class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)return false;
        unsigned int temp = x;
        unsigned int ans = 0;
        while(temp>0){
            ans=ans*10 + temp%10;
            temp /= 10;
        }
        return ans == x;
    }
};
