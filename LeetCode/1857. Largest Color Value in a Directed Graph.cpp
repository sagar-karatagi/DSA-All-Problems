// Author: Sagar Karatagi
// Date: May 26, 2025
// Time: 07:49
// Status: Accepted (83 / 83 testcases passed)
// Runtime: 287 ms (Beats 98.88%)
// Memory Usage: 147.93 MB (Beats 97.49%)

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> adj(n);       // Adjacency list for graph
        vector<int> indegree(n);          // Indegree array for topological sort
        
        // Build graph and indegree count
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            indegree[e[1]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);
        
        // dp[i][j] = max count of character j up to node i
        vector<array<int, 26>> dp(n);
        for (int i = 0; i < n; i++)
            dp[i].fill(0);
        
        int seen = 0, ans = 0;

        // Topological sort using Kahn’s algorithm
        while (!q.empty()) {
            int u = q.front(); q.pop();
            seen++;
            int c = colors[u] - 'a';
            dp[u][c]++;
            ans = max(ans, dp[u][c]);
            
            for (int v : adj[u]) {
                for (int k = 0; k < 26; k++)
                    dp[v][k] = max(dp[v][k], dp[u][k]);
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }
        
        // If not all nodes were seen, a cycle exists
        return seen == n ? ans : -1;
    }
};
