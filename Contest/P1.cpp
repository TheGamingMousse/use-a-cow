#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> len;
    for (int i = 0; i < n; i++) {
        if (s[i] == '#') continue;
        int st = i;
        while (i < n && s[i] == '.') {
            ++i;
        }
        len.pb(i - st);
    }
    int sum = 0;
    bool hasLong = false;
    for (int i : len) {
        if (i > 1) sum += 2;
        else sum++;
        if (i >= 3) {
            hasLong = true;
        }
    }
    if (hasLong) {
        cout << 2 << '\n';
    } else {
        cout << sum << '\n';
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}