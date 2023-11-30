#include<bits/stdc++.h>
using namespace std;
// kth ancestor for a tree
const int MX = 100005;
const int LOG = 20;
int up[LOG][MX];
int kth(int x, int d) {
    for (int i = LOG; i >= 0; i--) {
        int num = pow(2, i);
        if (d >= num) {
            x = up[i][x];
            d -= num;
        }
    }
    return x;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        up[0][max(x, y)] = min(x, y);
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    while (q--) {
        int x, k; cin >> x >> k;
        cout << kth(x, k) << "\n";
    }
}