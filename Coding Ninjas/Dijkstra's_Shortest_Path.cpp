#include <bits/stdc++.h> 
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {
   
    unordered_map<int,list<pair<int,int>> >adj;
    for(int i =0;i<vec.size();i++){
            int u= vec[i][0];
            int v = vec[i][1];
            int w = vec[i][2];
            adj[u].push_back(make_pair(w,v));
            adj[v].push_back(make_pair(w,u));
    }
    vector<int> ans(vertices,INT_MAX);
    set<pair<int,int>> s;
    ans[source] = 0;
    s.insert(make_pair(0,source)); 

    while(!s.empty()){
        auto top = *(s.begin());
        s.erase(s.begin());
        int TopDistance = top.first;
        int Node = top.second;

        for(auto neighbours:adj[Node]){

            if(TopDistance + neighbours.first < ans[neighbours.second]){
                auto record = s.find(make_pair(ans[neighbours.second],neighbours.second));
                if(record != s.end()){
                    s.erase(record);
                }
                ans[neighbours.second] = TopDistance + neighbours.first;
                s.insert(make_pair(TopDistance + neighbours.first,neighbours.second));
            }
        }
    } 
    return ans;  
}