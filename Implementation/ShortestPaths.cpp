#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
typedef long long ll;

int bellmanFord(int s, int d, int n, 
    vector<pair<pair<int, int>, int>>& edges) {
    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF), prev(n + 1, -1);
    dist[s] = 0;
    for (int i = 1; i < n; i++) {
        bool change = false;
        for (auto edge : edges) {
            int u = edge.f.f, v = edge.f.s, w = edge.s;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                change = 1;
            }
        }
        if (!change) break;
    }
    for (auto edge : edges) {
        int u = edge.f.f, v = edge.f.s, w = edge.s;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            return -1; // negative cycle
        }
    }
    return dist[d];
}
/*
Calculates distances between 
a starting node and every other 
node. Performs n - 1 edge relaxations
by iterating through all the edges.

Implementation details:
Just need a few vectors. Pretty simple.

Time complexity: O(VE);
*/
ll floydWarshall(int s, int d, int n, 
    vector<pair<pair<int, int>, int>>& edges) {
    const ll INF = 1e18;
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    for (auto i : edges) {
        dist[i.f.f][i.f.s] = min(dist[i.f.f][i.f.s], (ll)i.s);
        dist[i.f.s][i.f.f] = min(dist[i.f.s][i.f.f], (ll)i.s);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j],
                        dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist[s][d];
}
/*
Calculates distances between every
pair of nodes. Idea is for every pair
i, j of nodes, you can have a node k 
that acts as an intermediate node.
Use this to calculate all the distances.
Also good for detecting negative cycles.

Implementation details:
Adjacency matrix. If unsure about
the loop orders, just repeat it 3 times.

Time complexity: O(V^3)
*/
int dijkstra(int s, int d, int n, 
    vector<vector<pair<int, int>>> adj) {
    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>> q;
    dist[s] = 0; q.push({0, s});
    while (!q.empty()) {
        auto N = q.top(); q.pop();
        int p = N.s, t = N.f;
        if (dist[p] != t) continue;
        for (auto i : adj[p]) {
            int v = i.f, w = i.s;
            if (dist[p] + w < dist[v]) {
                dist[v] = dist[p] + w;
                q.push({-dist[v], v});
            }
        }
    }
    return dist[d];
}
/*
Calculates distances between
a starting node and all other nodes.
Idea is to use a priority queue,
and add nodes that have the current
"lowest" distance.

Implementation details:
Uses a priority queue and
a visited vector.

Time complexity: O(V + MlogM)
*/
int zeroOneBFS(int S, int D, int n,
    vector<vector<pair<int, int>>>& adj) {
    // zero indexed
    vector<int> d(n, 2e9);
    d[S] = 0;
    deque<int> q;
    q.push_front(S);
    while (!q.empty()) {
        int p = q.front();
        q.pop_front();
        for (auto& i : adj[p]) {
            int u = i.f, w = i.s;
            if (d[p] + w < d[u]) {
                d[u] = d[p] + w;
                if (w == 1) q.push_back(u);
                else q.push_front(u);
            }
        }
    }
    return d[D];
}
/*
Calculates distance between
a start and end node.
Special version of dijkstras
on a graph with edge weights
of only 0 & 1, for a better time
complexity.
*/