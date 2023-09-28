class Solution {
public:
    void rotate(vector<int>& nums, int k) { 
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        k %=nums.size();
        for(int i =0,j = nums.size()-k-1;i<j;i++,j--){
            swap(nums[i],nums[j]);
        }
        for(int i = nums.size()-k,j= nums.size()-1;i<j;i++,j--){
            swap(nums[i],nums[j]);
        }
        for(int i =0,j = nums.size()-1;i<j;i++,j--){
            swap(nums[i],nums[j]);
        }
    }
};
