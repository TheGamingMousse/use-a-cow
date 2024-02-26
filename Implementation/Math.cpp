#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 
 
const int MOD = 1e9 + 7;
const int N = 2e6 + 1;
ll fact[N], invFact[N];
template<class T> bool smin(T& a, T b) {
    return (b < a ? a = b, 1 : 0);
}
template<class T> bool smax(T& a, T b) {
    return (b > a ? a = b, 1 : 0);
}
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
ll inv(ll x) {
    return expo(x, MOD - 2);
}
ll binom(int n, int k) {
    return (fact[n] * invFact[k] % MOD * 
            invFact[n - k]) % MOD;
}
void calcFact() {
    fact[0] = 1, invFact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}