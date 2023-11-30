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
    int a, b, c; 
    cin >> a >> b >> c;
    bool b1 = (b + c) % 2;
    bool b2 = (a + c) % 2;
    bool b3 = (a + b) % 2;
    cout << !b1 << ' ' << !b2 
        << ' ' << !b3 << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Observation 1:
 * The parity of the digits
 * that are different is
 * an invariant.
 * 
 * Observation 2:
 * It only works if it's even.
*/