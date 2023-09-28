class Solution {
    bool solve(vector<int>& nums,int index,int target,vector<int>& dp){
        if(index>target)return false;
        if(index == target)return true;
        if(dp[index] != -1){
            return dp[index];
        }
        for(int i = 1;i<=nums[index];i++){    
            bool ans =  solve(nums,index+i,target,dp);
            dp[index+i] = ans;
            if(ans){
                return true;
            }
        }
        return false;
    }
public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(),-1);
        bool ans = solve(nums,0,nums.size()-1,dp);
        return ans;
    }
};
