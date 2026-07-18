#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build the adjacency list representation of the graph
        // graph[u] stores pairs of {v, weight}
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& edge : times) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        // Distance array initialized to infinity (a large value)
        const int INF = 1e9;
        vector<int> dist(n + 1, INF);
        
        // Min-heap priority queue storing pairs of {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Base case: Starting node k
        dist[k] = 0;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [curr_dist, u] = pq.top();
            pq.pop();

            // Skip processing if we already found a shorter path to u
            if (curr_dist > dist[u]) continue;

            // Explore neighbors
            for (const auto& neighbor : graph[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // Find the maximum time required to reach any node
        int max_time = 0;
        for (int i = 1; i <= n; ++i) {
            // If any node is unreachable, it's impossible for all nodes to receive the signal
            if (dist[i] == INF) return -1;
            max_time = max(max_time, dist[i]);
        }

        return max_time;
    }
};