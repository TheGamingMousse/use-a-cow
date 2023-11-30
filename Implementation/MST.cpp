#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second

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
/*
Union by size. Needed for Kruskal.
*/
ll kruskal(int n, vector<pair<
    pair<int, int>, int>>& edges) {
    sort(begin(edges), end(edges), [&](auto& x, auto& y) {
        return x.s < y.s;
    });
    DSU dsu(n); // 0 indexed
    ll cost = 0;
    for (auto& i : edges) {
        if (!dsu.connected(i.f.f, i.f.s)) {
            cost += i.s, dsu.unite(i.f.f, i.f.s);
        }
    }
    return (dsu.size(1) != n) ? -1 : cost;
}
/*
Sort the edges, and add the cheapest
edge that connects two components,
until the tree is connected or you
run out of edges.

Implementation details:
Needs a DSU.

Time complexity: O(ElogE)
*/
ll prim(int n, vector<vector<
    pair<int, int>>>& adj) {
    // adj list is {to_node, weight}
    vector<bool> vis(n); // 0 indexed
    vector<ll> dist(n, LONG_LONG_MAX);
    priority_queue<pair<int, int>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    ll cost = 0;
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        if (vis[p.s]) continue;
        vis[p.s] = 1, cost += -p.f;
        for (auto& i : adj[p.s]) {
            if (!vis[i.f] && i.s < dist[i.f]) {
                dist[i.f] = i.s;
                pq.push({-i.s, i.f});
            }
        }
    }
    return cost;
}
/*
Start from an arbitrary node, and 
add the "cheapest" unvisited nodes.
Similar to Dijkstra's.

Implementation details:
Priority queue used to
guarantee using the cheapest
edge available. Distance
vector used to either replace
suboptimal edges with more 
optimal edges and to prevent
potential "collisions".

Time complexity: O(ElogE)*
*Can also be done in O(V^2),
if the graph is densely populated
*/