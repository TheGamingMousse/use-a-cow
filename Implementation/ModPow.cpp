#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/** @return x^n % m */
ll modpow(ll x, ll n, ll m) {
    ll res = 1;
    for (x %= m; n; n >>= 1, (x *= x) %= m) {
        if (n & 1) (res *= x) %= m;
    }
    return res;
}