class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        unordered_map<int,int> dp;
        int ans =0;
        for(int i :arr){
            if(dp.find(i-difference) != dp.end()){
                dp[i] = dp[i-difference]+1;
            }else{
                dp[i] = 1;
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};