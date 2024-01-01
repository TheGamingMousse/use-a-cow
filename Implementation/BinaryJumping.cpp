#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5 + 1;
const int LOG = 18;
vector<int> adj[N];
int st[N], ed[N], e[N], 
    up[LOG][N], dep[N], t;
void tour(int node, int prev) {
    st[node] = t++;
    up[0][node] = prev;
    for (int i = 1; i < LOG; i++) {
        int ans = up[i - 1][node];
        up[i][node] = up[i - 1][ans];
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dep[i] = dep[node] + 1;
            tour(i, node);
        }
    }
    ed[node] = t;
}
int jump(int x, int d) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (1 & (d >> i)) {
            x = up[i][x];
        }
    }
    return x;
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    u = jump(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        int u1 = up[i][u], v1 = up[i][v];
        if (u1 != v1) u = u1, v = v1;
    }
    return up[0][u];
}
/**
 * LCA, using binary jumping. Note that
 * you don't need DFS, but I'm too lazy
 * to remove the Euler Tour code.
 * 
 * Note for Euler Tour: if you ever want
 * to query values for some paths, undo
 * said operation at the end of each tour.
 * 
 * Another note for Euler Tour: if the queries
 * are offline / one query won't affect the next
 * query, then you should consider changing the
 * order in which each query is processed.
 * 
 * Note for Binary Jumping: You can actually use
 * it to query paths, assuming you also use
 * LCA. Basically, discount HLD.
*/