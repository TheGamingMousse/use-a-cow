#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(begin(a), end(a),
        greater<int>());
    vector<ll> sum(n);
    vector<int> factors(1e5 + 1);
    for (int i = n - 1; i >= 0; i--) {
        vector<int> temp;
        cout << a[i] << ": ";
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                temp.pb(j);
                temp.pb(a[i] / j);
            }
            cout << j << ' ' << a[i] / j << ' ';
        }
        cout << '\n';
        if (size(temp) == 2) {
            sum[i] += factors[1];
            sum[i] += factors[a[i]] * a[i];
        } else {
            for (int j : temp) {
                if (j != 1) {
                    sum[i] += factors[j] * j;
                }
            }
        }
        for (int j : temp) {
            factors[j]++;
        }
    }
    vector<ll> suffix(n);
    suffix[n - 1] = sum.back();
    for (int j = n - 2; j >= 0; j--) {
        suffix[j] = sum[j] + suffix[j + 1];
    }
    ll res = 0;
    for (int i = 1; i < n; i++) {
        res += suffix[i];
    }
    cout << res << '\n';
    for (ll i : sum) {
        cout << i << ' ';
    }
    cout << '\n';
    for (int i = 0; i <= n; i++) {
        cout << factors[i] << ' ';
    }
}
int main() {
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
/**
 * Observation 1:
 * Sorting is legal, allowing
 * us to bypass the annoying 
 * sorted order thing.
 * 
 * Observation 2:
 * With observation 1, once we know
 * the sum of GCDs for each element,
 * you can solve the rest in O(N).
 * 
 * Key Issue:
 * HOW TO GET OTHER ELEMENTS IN O(N)
 * AAAAAAAA
 * Answer: GCD sum = sum of occurences
 * of each factor, * the thingy mbobber
*/