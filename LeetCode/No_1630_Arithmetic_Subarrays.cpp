class Solution {
public:
    bool isArithmetic(vector<int> nums, int l, int r) {
        if (r - l < 2) {
            return true;
        }
        sort(nums.begin()+l,nums.begin()+r);
        int commonDifference = nums[l + 1] - nums[l];
        for (int i = l + 1; i < r; i++) {
            if (nums[i] - nums[i - 1] != commonDifference) {
                return false;
            }
        }
        return true;
    }

    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int size = l.size();
        vector<bool> ans;
        for (int i = 0; i < size; i++) {
            int begin = l[i];
            int end = r[i];
            ans.push_back(isArithmetic(nums, begin, end+1));
        }
        return ans;
    }
};
