// Author: Sagar Karatagi
// Date: May 28, 2025
// LeetCode 3372 - Maximize the Number of Target Nodes After Connecting Trees I

class Solution {
public:
    // DFS to count number of reachable nodes within distance k from a given node
    int dfs(int node, int parent, const vector<vector<int>>& children, int k) {
        if (k < 0) return 0;
        int res = 1; // count self
        for (int child : children[node]) {
            if (child == parent) continue; // avoid going back
            res += dfs(child, node, children, k - 1);
        }
        return res;
    }

    // Builds adjacency list and computes reachable nodes for all nodes
    vector<int> build(const vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> children(n);
        for (const auto& edge : edges) {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }

        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = dfs(i, -1, children, k);
        }
        return res;
    }

    // Main function
    vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                               vector<vector<int>>& edges2, int k) {
        int n = edges1.size() + 1;
        vector<int> count1 = build(edges1, k);       // Targets from Tree 1
        vector<int> count2 = build(edges2, k - 1);   // Targets from Tree 2
        int maxCount2 = *max_element(count2.begin(), count2.end());

        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = count1[i] + maxCount2; // Best possible connection
        }
        return res;
    }
};
