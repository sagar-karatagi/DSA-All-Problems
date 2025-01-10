class Solution {
public:
    int minPairSum(vector<int>& nums) {
ios_base::sync_with_stdio(false);
cin.tie(nullptr);
cout.tie(nullptr);
        sort(nums.begin(),nums.end());
        int ans = INT_MIN;
        int j = nums.size()-1;
        for(int i =0;i<j;i++,j--){
            if(nums[i] + nums[j] > ans){
                ans  = nums[i]+nums[j];
            }
        }
        return ans;
    }
};
