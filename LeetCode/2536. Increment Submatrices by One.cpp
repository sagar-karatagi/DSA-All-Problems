//Author : Sagar Karatagi
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n,vector<int>(n+1,0));
        //The problem is just using the difference array in 2-D world 
        for(auto q:queries){
            int r1 = q[0];
            int c1 = q[1];
            int r2 = q[2];
            int c2 = q[3];
          //For each 1-D diff array increment start and decrement end+1
            for(int r = r1;r<=r2;r++){
                diff[r][c1]++;
                diff[r][c2+1]--;
            }
        }
        for(int i = 0;i<n;i++){
            int cnt = 0;
            for(int j = 0;j<n;j++){
                cnt+=diff[i][j];
                diff[i][j]= cnt;
            }
          //Pop the extra element we had in each row while init
            diff[i].pop_back();
        }
        return diff;
    }
};
