// ============================================================================
// 7B — MULTI-SOURCE BFS : ROTTING ORANGES / SHORTEST PATH IN A GRID
// ============================================================================
// TRIGGER WORDS : "how many minutes until everything is reached" · "spread to
//                 all neighbours each step" · "shortest path in a grid where
//                 every move costs 1"
//
// THE KEY IDEA : push ALL sources into the queue before the loop starts. BFS
//     then expands them in lockstep, so the level number IS the answer. Running
//     one BFS per source is the mistake.
//
// TRAP : answer = levels - 1 (the initial level costs no minutes).
// TRAP : check afterwards that nothing is left unreached -> return -1.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

static const int DR[4] = {1,-1,0,0}, DC[4] = {0,0,1,-1};

// 0 empty, 1 fresh, 2 rotten. Returns minutes, or -1 if some fresh survives.
int orangesRotting(vector<vector<int>> g) {
    int n = (int)g.size(), m = n ? (int)g[0].size() : 0, fresh = 0, minutes = 0;
    queue<pair<int,int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 2) q.push({i,j});     // ALL sources go in first
            else if (g[i][j] == 1) fresh++;
        }
    if (!fresh) return 0;
    while (!q.empty() && fresh) {
        int sz = (int)q.size();                  // one whole level = one minute
        while (sz--) {
            auto [r,c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r+DR[d], nc = c+DC[d];
                if (nr<0||nc<0||nr>=n||nc>=m||g[nr][nc]!=1) continue;
                g[nr][nc] = 2; fresh--; q.push({nr,nc});
            }
        }
        minutes++;
    }
    return fresh ? -1 : minutes;
}

// shortest path length from (0,0) to (n-1,m-1) over open cells (0 = open)
int shortestGridPath(vector<vector<int>> g) {
    int n = (int)g.size(), m = n ? (int)g[0].size() : 0;
    if (!n || g[0][0] || g[n-1][m-1]) return -1;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q; q.push({0,0}); dist[0][0] = 0;
    while (!q.empty()) {
        auto [r,c] = q.front(); q.pop();
        if (r == n-1 && c == m-1) return dist[r][c];
        for (int d = 0; d < 4; d++) {
            int nr = r+DR[d], nc = c+DC[d];
            if (nr<0||nc<0||nr>=n||nc>=m||g[nr][nc]||dist[nr][nc]!=-1) continue;
            dist[nr][nc] = dist[r][c] + 1; q.push({nr,nc});
        }
    }
    return -1;
}

// TIME O(n*m)   SPACE O(n*m)
// ---------------------------------------------------------------------------
int main() {
    assert(orangesRotting({{2,1,1},{1,1,0},{0,1,1}}) == 4);
    assert(orangesRotting({{2,1,1},{0,1,1},{1,0,1}}) == -1);
    assert(orangesRotting({{0,2}}) == 0);
    assert(shortestGridPath({{0,0,0},{1,1,0},{0,0,0}}) == 4);
    assert(shortestGridPath({{0,1},{1,0}}) == -1);
    puts("7b  multi-source BFS        OK");
}
