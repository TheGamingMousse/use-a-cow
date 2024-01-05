#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 2e5;
vector<pii> adj[N];
ll dp[N], len[N], deg[N], s[N];
bool vis[N];
void dfs(int node) {
    vis[node] = true;
    for (auto [v, w] : adj[node]) {
        if (!vis[v]) dfs(v);
        ckmax(len[node], len[v] + 1);
    }
    vector<pair<ll, pair<ll, ll>>> sums;
    for (auto [v, w] : adj[node]) {
        if (len[v] + 1 == len[node]) {
            sums.pb({dp[v], {w, s[v]}});
        }
    }
    sort(all(sums), [&](auto& x, auto& y) {
        if (x.s.f == y.s.f) {
            if (x.s.s == y.s.s) {
                return x.f < y.f;
            }
            return x.s.s < y.s.s;
        }
        return x.s.f < y.s.f;
    });
    if (sz(sums)) {
        dp[node] = sums[0].f + sums[0].s.f;
        s[node] = sums[0].s.f;
    }
}
int main() { 
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        adj[--x].pb({--y, l});
        deg[y]++;
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) pq.push(-i);
    }
    vector<int> toposort;
    while (!pq.empty()) {
        int u = -pq.top(); pq.pop();
        toposort.pb(u);
        for (auto [v, w] : adj[u]) {
            --deg[v];
            if (!deg[v]) {
                pq.push(-v);
            }
        }
    }
    for (int i : toposort) {
        if (!vis[i]) dfs(i);
    }
    for (int i = 0; i < n; i++) {
        cout << len[i] << ' ' << dp[i] << '\n';
    }
}
/**
 * TASK: Minimum Longest Trip.
 * Algorithm: Toposort then DFS.
*/