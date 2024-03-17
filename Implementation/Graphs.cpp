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
struct DSU {
    vector<int> e;
    DSU(int n) { e = vector<int>(n, -1); }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
namespace SCC {
    int n, ti, nc; // nc = # of SCCs
    vector<int> st, num, low;
    vector<vector<int>> adj;
    vector<bool> vis;
    void dfs(int u) {
        num[u] = low[u] = ti++;
        st.push_back(u);
        vis[u] = true;
        for (int v : adj[u]) {
            if (num[v] == -1) dfs(v);
            if (vis[v]) smin(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            for (int v = -1; v != u;) {
                v = st.back(), st.pop_back();
                low[v] = nc, vis[v] = false;
            }
            nc++;
        }
    }
    void build(int sz) {
        adj.resize(sz + 5), num.resize(sz + 5), 
        low.resize(sz + 5), vis.resize(sz + 5);
        n = sz;
    }
    void init() {
        ti = nc = 0, fill(all(num), -1);
        for (int i = 0; i < n; i++) {
            if (num[i] == -1) dfs(i);
        }
    }
    void compress() {
        vector<array<int, 2>> edges;
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) if (low[i] != low[j]) {
                edges.push_back({low[i], low[j]});
            }
        }
        sort(all(edges));
        edges.erase(unique(all(edges)), end(edges));
        adj = vector(nc, vector<int>());
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
        }
    }
};