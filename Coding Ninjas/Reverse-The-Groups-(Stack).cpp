void solve(stack<int>& s,int size,int k){

    if(size - k< 0) return;
    queue<int> q;
    int i =k;
    while(i!=0){
        q.push(s.top());
        s.pop();
        i--;
    }
    solve(s,size -k,k);
    while(!q.empty()){
        s.push(q.front());
        q.pop();
    }
   
}
stack<int> reverseTheGroups(stack<int> &s, int n, int k) {
    solve(s,n,k);
    return s;
}