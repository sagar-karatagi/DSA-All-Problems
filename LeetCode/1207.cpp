class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> m;
        for(int i =0;i<arr.size();i++){
            m[arr[i]]++;
        }
        unordered_map<int,bool> m1;
        for(auto i:m){
            if(m1[i.second]){
                return false;
            }
            m1[i.second] = true;
        }
        return true;
    }
};