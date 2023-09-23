#include <bits/stdc++.h>
vector<int> nextSmallerElement(vector<int> &arr, int n){ 
    vector<int> ans(n);
    stack<int> s;
    s.push(-1);

    for(int i = n-1;i>-1;i--){
        while(s.top()>=arr[i]){
            s.pop();
        }
        ans[i]=s.top();
        s.push(arr[i]);
    }

    return ans;
}