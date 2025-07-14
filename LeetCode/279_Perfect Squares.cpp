class Solution {
    bool isPerfectSquare(int n) {
        int root = (int)sqrt(n);
        return root * root == n;
    }
    bool fermat(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) {
                    n /= i;
                    ++cnt;
                }
                if (i % 4 == 3 && cnt % 2 != 0) {
                    return false;
                }
            }
        }
        return n%4!=3;
    }
    bool legendre(int n) {
        while (n % 4 == 0)
            n /= 4;
        return n % 8 != 7;
    }

public:
    int numSquares(int n) {

        if (isPerfectSquare(n)) {
            return 1;
        } else if (fermat(n)) {
            return 2;
        } else if (legendre(n)) {
            return 3;
        }
        return 4;
    }
};
