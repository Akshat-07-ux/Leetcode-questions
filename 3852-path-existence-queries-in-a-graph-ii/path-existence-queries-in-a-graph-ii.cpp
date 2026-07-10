class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> v;
        v.reserve(n);
        for (int i = 0; i < n; i++)
            v.push_back({nums[i], i});

        sort(v.begin(), v.end());

        vector<int> posInSorted(n);
        for (int i = 0; i < n; i++)
            posInSorted[v[i].second] = i;

        // Component IDs (split whenever consecutive gap > maxDiff)
        vector<int> comp(n);
        int cid = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (v[i].first - v[i - 1].first > maxDiff)
                cid++;
            comp[i] = cid;
        }

        // Furthest index reachable in one edge from each sorted position.
        vector<int> reach(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n && v[r + 1].first - v[i].first <= maxDiff)
                r++;
            reach[i] = r;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = reach;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][ up[k - 1][i] ];
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int u = q[0], w = q[1];
            if (u == w) {
                ans.push_back(0);
                continue;
            }

            int a = posInSorted[u];
            int b = posInSorted[w];
            if (a > b) swap(a, b);

            if (comp[a] != comp[b]) {
                ans.push_back(-1);
                continue;
            }

            int cur = a;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < b) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
};