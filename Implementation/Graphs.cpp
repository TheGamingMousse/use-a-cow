#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
void dfs1(int node, vector<bool>& vis,
    vector<vector<int>>& adj) {
    vis[node] = 1;
    for (int i : adj[node]) {
        if (!vis[i]) dfs1(i, vis, adj);
    }
}
void dfs2(int node, int prev,
    vector<vector<int>>& adj) {
    for (int i : adj[node]) {
        if (i != prev) dfs2(i, node, adj);
    }
}
void bfs(int node, vector<vector<int>>& adj) {
    vector<bool> vis;
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int p = q.front(); 
        q.pop();
        vis[p] = 1;
        for (int i : adj[p]) {
            if (!vis[i]) q.push(i);
        }
    }
}
void ff(int r, int c, int MAXR, int MAXC,
    int color, vector<vector<int>>& grid,
    vector<vector<bool>>& vis) {
    if (r < 0 || r >= MAXR || c < 0 || c >= MAXC
        || grid[r][c] != color || vis[r][c]) {
        return;
    }
    vis[r][c] = 1;
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        ff(r + dr[i], c + dc[i], MAXR, MAXC, color, grid, vis);
    }
}