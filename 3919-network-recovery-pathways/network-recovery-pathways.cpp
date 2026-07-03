#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
private:
    // Helper function to get the topological sort of the DAG
    vector<int> getTopologicalSort(int n, const vector<vector<pair<int, int>>>& adj) {
        vector<int> inDegree(n, 0);
        for (int u = 0; u < n; ++u) {
            for (auto& edge : adj[u]) {
                inDegree[edge.first]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            
            for (auto& edge : adj[u]) {
                int v = edge.first;
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        return topoOrder;
    }

public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // Build adjacency list: adj[u] = {v, cost}
        vector<vector<pair<int, int>>> adj(n);
        int max_cost = 0;
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            max_cost = max(max_cost, edge[2]);
        }
        
        // Precompute topological sort for the DAG
        vector<int> topoOrder = getTopologicalSort(n, adj);
        
        // Binary search range for the minimum edge cost
        int low = 0, high = max_cost;
        int ans = -1;
        
        const long long INF = 1e18; // Use a sufficiently large value for infinity
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // DP array to find the shortest path filtering edges < mid
            vector<long long> dist(n, INF);
            dist[0] = 0;
            
            for (int u : topoOrder) {
                if (dist[u] == INF || !online[u]) continue;
                
                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int cost = edge.second;
                    
                    // Only traverse if the edge cost >= mid and destination is online
                    if (cost >= mid && online[v]) {
                        if (dist[u] + cost < dist[v]) {
                            dist[v] = dist[u] + cost;
                        }
                    }
                }
            }
            
            // Check if node n-1 is reachable within budget k
            if (dist[n - 1] <= k) {
                ans = mid;       // mid is a valid score, try to find a larger one
                low = mid + 1;
            } else {
                high = mid - 1;  // mid is too restrictive, lower the threshold
            }
        }
        
        return ans;
    }
};