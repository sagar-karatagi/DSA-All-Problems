class Solution {
    int solve(vector<int>& nums, vector<int>& dp,int index,const int& target){
        if(nums[index] == 0 && index != target){
            dp[index] = INT_MAX-1;
        }
        if(dp[index]!=-1)return dp[index];
        int ans = INT_MAX-1;
        for(int i = 1;i<= nums[index] && index + i <=target;i++){  
            dp[index + i] = solve(nums,dp,index + i,target);
            ans = min(dp[index+i],ans);
        }
        dp[index] = ans + 1;
        return ans+1;
    }
public:
    int jump(vector<int>& nums) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int size = nums.size();
        if(size == 1) return 0;
        vector<int> dp(nums.size(),-1);
        dp[size-1] = 0;
        int ans = solve(nums,dp,0,size-1);
        for(auto i:dp){
            cout<<i<<" ";
        }
        return ans;
    }
};
