#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 
    
const int N = 1e5 + 1;
vector<int> adj[N];
ll ways[N], n, m;
void dfs1(int node, int prev) {
    ways[node] = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs1(i, node);
            ways[node] *= ways[i] + 1;
            ways[node] %= m;
        }
    }
}
void dfs2(int node, int prev) {
    if (node != 1) {
        ll above = ways[prev] 
            / (ways[node] + 1);
        ways[node] *= (above + 1);
        ways[node] %= m;
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs2(i, node);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << ways[i] << '\n';
    }
}
/**
 * Observation:
 * All the black vertices
 * must be in a connected component.
 * (Basically, tree DP then rerooting)
*/