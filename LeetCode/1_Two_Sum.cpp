class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> v = nums;
        int num1;
        int num2;
        sort(v.begin(),v.end());
        for(int i =0,j=v.size()-1;i<j;){
            if(v[i]+v[j]==target){
                num1 = v[i];
                num2 = v[j];
                break;
            }else if(v[i] + v[j] < target){
                i++;
            }else{
                j--;
            }      
        }
        vector<int> ans(2,-1);
        int n =0;
        for(int i =0;i<nums.size();i++){
            if(nums[i]==num1||nums[i]==num2 && ans[n] != i){
                ans[n] = i;
                n++;
            }
        }
        return ans;
    }
};
