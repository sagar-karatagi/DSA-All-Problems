class Solution {
public:
    string makeFancyString(string s) {
        string ans ;
        int n = s.size();
        int i,j;
        i = 0;
        while(i<n){
            ans+=s[i];
            int j = i+1;
            while(j<n&&s[i]==s[j])++j;
            if(j-i+1>2){
                ans+=s[i];
            }
            i = j;
        }
        return ans;
    }
};
