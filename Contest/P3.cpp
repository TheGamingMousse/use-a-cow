#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 3e5 + 1;
vector<int> adj[MAX];
char dir[MAX];
int dp[MAX][2];
// node, left, right
void dfs(int node) {
    if (node == 0 ||
        (!adj[node][0]
        && !adj[node][1])) {
        return;
    }
    // left
    int left = adj[node][0],
        right = adj[node][1];
    if (left != 0) {
        dfs(left);
        dp[node][0] = min(dp[left][0],
            dp[left][1]);
        if (dir[node] != 'L') {
            ++dp[node][0];
        }
    } else {
        dp[node][0] = 2e9;
    }
    // right
    if (right != 0) {
        dfs(right);
        dp[node][1] = min(dp[right][0],
            dp[right][1]);
        if (dir[node] != 'R') {
            ++dp[node][1];
        }
    } else {
        dp[node][1] = 2e9;
    }
}
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> dir[i];
        dp[i][0] = 0;
        dp[i][1] = 0;
    }
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        adj[i] = {a, b};
    }
    dfs(1);
    int res = 2e9;
    if (adj[1][0]) {
        res = min(res, dp[1][0]);
    }
    if (adj[1][1]) {
        res = min(res, dp[1][1]);
    }
    cout << res << '\n';
    /*
    for (int i = 1; i <= n; i++) {
        cout << dp[i][0] << ' ' << dp[i][1] << '\n';
    }
    */
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        solve();
    }
}
/**
 * For each subtree, count
 * min ops to reach leaf node
 * 4
RULR
3 0
0 0
0 4
2 0
*/