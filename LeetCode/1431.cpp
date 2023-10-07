class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {  
        int maxi = INT_MIN;
				//Find the maximum element 
        for(auto i:candies){
            if(i>maxi)
                maxi = i;
        }
        vector<bool> ans(candies.size(),0);
        for(int i =0;i<candies.size();i++){
						//Truth condition as per question
            if(candies[i] + extraCandies >= maxi)
                ans[i] = 1;
        }
        return ans;
    }
};
