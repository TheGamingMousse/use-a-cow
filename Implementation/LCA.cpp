#include <bits/stdc++.h>
using namespace std;

#include "RMQ1.cpp"

class LCA {
    private:
        const int n;
        const vector<vector<int>> &adj;
        RMQ<array<int, 2>> rmq;
        vector<int> tin, et, dep;
        int timer = 0;
        void dfs(int u, int p) {
            tin[u] = timer;
            et[timer++] = u;
            for (int v : adj[u]) {
                if (v == p) continue;
                dep[v] = dep[u] + 1;
                dfs(v, u);
                et[timer++] = u;
            }
        }
    public:
        LCA(int _n, vector<vector<int>> &_adj) 
            : n(_n), adj(_adj), tin(n), et(2 * n), dep(n) {
            dfs(0, -1);
            vector<array<int, 2>> arr(2 * n);
            for (int i = 0; i < 2 * n; i++) {
                arr[i] = {dep[et[i]], et[i]};
            }
            rmq.init(arr);
        }
        int query(int a, int b) {
            if (tin[a] > tin[b]) swap(a, b);
            return rmq.query(tin[a], tin[b])[1];
        }
};