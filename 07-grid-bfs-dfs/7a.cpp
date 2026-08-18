// ============================================================================
// 7A — GRID FLOOD FILL : NUMBER OF ISLANDS (LC 200)
// ============================================================================
// TRIGGER WORDS : "count islands / regions / connected groups" · "surrounded
//                 regions" · "size of the largest region" · a 2-D char/int grid
//
// THE SHAPE : scan every cell; when you meet an unvisited land cell, increment
//             the counter and flood the whole component so it is never counted
//             again. Sinking the land in-place ('1' -> '0') is the cheapest way
//             to mark visited — say so out loud if asked about extra space.
//
// TRAP : recursion depth. A 1000x1000 all-land grid is 10^6 deep and blows the
//        stack. The iterative BFS below is the safe default in an OA.
// TRAP : bounds check BEFORE indexing, and remember the grid may be empty.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

static const int DR[4] = {1,-1,0,0}, DC[4] = {0,0,1,-1};

int numIslandsBFS(vector<vector<char>> g) {   // by value: we sink land in place
    if (g.empty() || g[0].empty()) return 0;
    int n = (int)g.size(), m = (int)g[0].size(), count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '1') continue;
            count++;
            queue<pair<int,int>> q;
            q.push({i,j}); g[i][j] = '0';     // mark on PUSH, never on pop
            while (!q.empty()) {
                auto [r,c] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                    if (g[nr][nc] != '1') continue;
                    g[nr][nc] = '0';
                    q.push({nr,nc});
                }
            }
        }
    return count;
}

// recursive DFS — shorter, but watch the stack on big grids
static void sink(vector<vector<char>>& g, int r, int c) {
    if (r < 0 || c < 0 || r >= (int)g.size() || c >= (int)g[0].size() || g[r][c] != '1') return;
    g[r][c] = '0';
    for (int d = 0; d < 4; d++) sink(g, r + DR[d], c + DC[d]);
}
int numIslandsDFS(vector<vector<char>> g) {
    if (g.empty() || g[0].empty()) return 0;
    int count = 0;
    for (int i = 0; i < (int)g.size(); i++)
        for (int j = 0; j < (int)g[0].size(); j++)
            if (g[i][j] == '1') { count++; sink(g, i, j); }
    return count;
}

int largestIslandArea(vector<vector<char>> g) {
    if (g.empty() || g[0].empty()) return 0;
    int n = (int)g.size(), m = (int)g[0].size(), best = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '1') continue;
            int area = 0;
            queue<pair<int,int>> q; q.push({i,j}); g[i][j] = '0';
            while (!q.empty()) {
                auto [r,c] = q.front(); q.pop(); area++;
                for (int d = 0; d < 4; d++) {
                    int nr = r+DR[d], nc = c+DC[d];
                    if (nr<0||nc<0||nr>=n||nc>=m||g[nr][nc]!='1') continue;
                    g[nr][nc]='0'; q.push({nr,nc});
                }
            }
            best = max(best, area);
        }
    return best;
}

// TIME O(n*m)   SPACE O(n*m) worst case for the queue
// ---------------------------------------------------------------------------
int main() {
    vector<vector<char>> g = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}};
    assert(numIslandsBFS(g) == 3);
    assert(numIslandsDFS(g) == 3);
    assert(largestIslandArea(g) == 4);
    assert(numIslandsBFS({}) == 0);
    assert(numIslandsBFS({{'0'}}) == 0);
    puts("7a  number of islands       OK");
}
