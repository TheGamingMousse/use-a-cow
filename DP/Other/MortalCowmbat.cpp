#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define f first 
#define s second 

const int N = 1e5;
const int M = 26;
ll dp[N + 1][M], pf[N + 1][M];
int dist[M][M];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    int n, m, k; string s;
    cin >> n >> m >> k >> s;
    s = " " + s; // 1 indexing
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> dist[i][j];
        }
    }
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                smin(dist[i][j], dist[i][k] + dist[k][j]);
                smin(dist[j][i], dist[j][k] + dist[k][i]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {          
            pf[i][j] = pf[i - 1][j] + dist[s[i] - 'a'][j];
            dp[i][j] = 1e18;
        }
    }
    vector<ll> best(n + 1, 1e18);
    best[0] = 0;
    for (int i = k; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = min(dp[i - 1][j] + dist[s[i] - 'a'][j], 
                best[i - k] + pf[i][j] - pf[i - k][j]);
            smin(best[i], dp[i][j]);
        }
    }
    cout << best[n] << '\n';
}
/**
 * Consider the following:
 * dp[i][j] = minimum days to form a valid set of
 * instructions up to the i-th day, with the last
 * character being j.
 * 
 * State transitions:
 * dp[i][j] = min(dp[i - 1][j] + dist[s[i]][j,
 *      min(dp[i - k][all m]) + pf[i][j] - pf[i - k][j]).
 * 
 * Note: we use prefix sums to quickly calculate changes
 * needed to change a subarray to a character m.
*/