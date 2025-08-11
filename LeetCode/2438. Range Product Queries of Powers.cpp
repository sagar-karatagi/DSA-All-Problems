class Segtree {
    int n;
    vector<long long> tree;
    const int mod = 1e9 + 7;

public:
    Segtree(const vector<int>& powers) {
        n = 1;
        int size = powers.size();
        while (n < size)
            n <<= 1;
        tree.assign(2 * n, 1);

        for (int i = 0; i < size; i++) {
            tree[i + n] = powers[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = (tree[2 * i] * tree[2 * i + 1]) % mod;
        }
    }

    int query(int l, int r) {
        l += n;
        r += n + 1;
        long long l_res = 1, r_res = 1;
        while (l < r) {
            if (l & 1)
                l_res = (l_res * tree[l++]) % mod;
            if (r & 1)
                r_res = (r_res * tree[--r]) % mod;
            l >>= 1;
            r >>= 1;
        }
        return (l_res * r_res) % mod;
    }
};

class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> powers;
        for (int i = 0; i < 32; i++) {
            if (n & (1 << i)) {
                powers.push_back(1 << i);
            }
        }
        Segtree seg(powers);
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            ans[i] = seg.query(l, r);
        }
        return ans;
    }
};
