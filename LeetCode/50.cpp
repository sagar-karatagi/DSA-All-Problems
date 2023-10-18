class Solution {
    double solve(double x,int n){
        if(n == 0 )return 1;
        if(n == 1) return x;
        double ans = solve(x,n/2);
        return (n%2 == 0)?ans*ans:x*ans*ans;
    }
public:
    double myPow(double x, int n) {
        return (n<0)?1.0/solve(x,n):solve(x,n);
    }
};
