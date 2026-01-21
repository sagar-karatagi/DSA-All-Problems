//Author : Sagar Karatagi
//Date : 21-01-2016

/*
Flip each bit and check if it can form nums[i]
*/
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, INT_MAX);
        for (int i = 0; i < nums.size(); i++) {

            for (int x = 0; x < 32; x++) {
                int temp = nums[i] ^ (1 << x);
                if ((temp | (temp + 1)) == nums[i]) {
                    ans[i] = min(ans[i], temp);
                } else if ((temp | (temp - 1)) == nums[i]) {
                    ans[i] = min(ans[i], temp - 1);
                }
            }
            if (ans[i] == INT_MAX) {
                ans[i] = -1;
            }
        }
        return ans;
    }
};
