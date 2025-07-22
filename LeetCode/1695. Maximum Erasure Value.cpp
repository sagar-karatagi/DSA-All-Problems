class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        vector<int> freq(10001, 0); 
        int max_sum = 0;
        int current_sum = 0;
        int i = 0;
        for (int j = 0; j < nums.size(); ++j) {
            current_sum += nums[j];
            freq[nums[j]]++;
            while (freq[nums[j]] > 1) {
                current_sum -= nums[i];
                freq[nums[i]]--;
                i++;
            }
            max_sum = max(max_sum, current_sum);
        }
        return max_sum;
    }
};
