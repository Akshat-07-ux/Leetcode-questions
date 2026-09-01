#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int maxEnergy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startR = -1, startC = -1;
        vector<pair<int, int>> litters;
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    startR = r;
                    startC = c;
                } else if (classroom[r][c] == 'L') {
                    litters.push_back({r, c});
                }
            }
        }
        
        int numLitter = litters.size();
        if (numLitter == 0) return 0;
        
        int targetMask = (1 << numLitter) - 1;
        
        // dist[r][c][mask] stores the maximum remaining energy achieved at (r, c) with state mask
        vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(1 << numLitter, -1)));
        
        // Queue for BFS: {r, c, mask, energy}
        queue<tuple<int, int, int, int>> q;
        
        // Initial state
        int initialMask = 0;
        // Check if start position itself is a litter (though usually S is distinct)
        for (int i = 0; i < numLitter; ++i) {
            if (litters[i].first == startR && litters[i].second == startC) {
                initialMask |= (1 << i);
            }
        }
        
        // If starting on 'R', energy is full, but standard start energy is maxEnergy anyway
        dist[startR][startC][initialMask] = maxEnergy;
        q.push({startR, startC, initialMask, maxEnergy});
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        int moves = 0;
        
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();
                
                if (mask == targetMask) {
                    return moves;
                }
                
                // If energy is 0 and we are not at a reset cell 'R', we cannot move.
                // If we are at 'R', energy resets back to maxEnergy.
                if (classroom[r][c] == 'R') {
                    e = maxEnergy;
                }
                
                if (e == 0) continue; // Cannot make any moves if energy is 0 and not at 'R'
                
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int ne = e - 1;
                        int nmask = mask;
                        
                        // Check if new position is an uncollected litter
                        if (classroom[nr][nc] == 'L') {
                            for (int i = 0; i < numLitter; ++i) {
                                if (litters[i].first == nr && litters[i].second == nc) {
                                    nmask |= (1 << i);
                                    break;
                                }
                            }
                        }
                        
                        // If new cell is 'R', energy gets restored to full maxEnergy upon arrival
                        if (classroom[nr][nc] == 'R') {
                            ne = maxEnergy;
                        }
                        
                        if (ne > dist[nr][nc][nmask]) {
                            dist[nr][nc][nmask] = ne;
                            q.push({nr, nc, nmask, ne});
                        }
                    }
                }
            }
            moves++;
        }
        
        return -1;
    }
};