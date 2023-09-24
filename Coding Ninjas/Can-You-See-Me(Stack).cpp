int countPairs(int n, vector<int> &arr) {
    
    unordered_map<int,vector<int>>m;
    stack<int> s;
    s.push(INT_MAX);
    for(int i = arr.size()-1;i>-1;i--){
        while(arr[i]>=s.top()){
            m[i].push_back(s.top());
            s.pop();
        }
        if(s.top()!=INT_MAX){
            m[i].push_back(s.top());
        }
        s.push(arr[i]);
    }
    int ans =0;
    for(auto i:m){
        ans+=i.second.size();
    }
    return ans;
}

