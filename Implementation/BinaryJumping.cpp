#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
namespace LCA {
    int n, LOG;
    vector<vector<int>> adj, up;
    vector<int> depth;
    void init(int sz) {
        n = sz, LOG = 31 - __builtin_clz(sz);
        adj = vector<vector<int>>(n);
        up = vector(LOG, vector(n, 0));
        depth = vector<int>(n);
    }
    void build() {
        auto dfs = [&](int u, int p, auto&& dfs) -> void {
            for (int i = 1; i < LOG; i++) {
                up[i][u] = up[i - 1][up[i - 1][u]];
            }
            for (int v : adj[u]) if (v != p) {
                up[0][v] = p, depth[v] = depth[u] + 1;
                dfs(v, u, dfs);
            }
        }; dfs(0, -1, dfs);
    }
    int lift(int x, int d) {
        for (int i = LOG - 1; i >= 0; i--) {
            if (d >> i & 1) x = up[i][x];
        }
        return x;
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u], v = up[i][v];
            }
        }
        return up[0][u];
    }
    int dist(int u, int v, int anc = -1) {
        if (anc == -1) anc = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[anc];
    }
};