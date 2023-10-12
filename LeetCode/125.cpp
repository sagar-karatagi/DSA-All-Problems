class Solution {
public:
    bool isPalindrome(string s) {
        string ans;
        for(auto i:s){
            if((i<='Z' && i>='A') || (i<='z' && i>='a')){
                ans+=tolower(i);
            }else if(i<='9' && i>='0'){
                ans+=i;
            }
        }
        for(int i = 0,n =ans.size()-1;i<n;i++,n--){
            if(ans[i] != ans[n])return 0;
        }
       return 1; 
    }
};
