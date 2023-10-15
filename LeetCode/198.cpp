class Solution {
    int solve(vector<int>&dp,vector<int>& nums,int index,const int& size){
        //Base cases
        if(index >size)return 0;
        if(index == size) return nums[index];

        if(dp[index] != INT_MIN) return dp[index];
        int i = nums[index] + solve(dp,nums,index+2,size);
        int j = nums[index+1] + solve(dp,nums,index+3,size);
        return  dp[index] = max(i,j);
    }
public:
    int rob(vector<int>& nums) {
        int size = nums.size() -1;
        int index = 0;
        vector<int> dp(size+1,INT_MIN);
        return solve(dp,nums,index,size);
    }
};
