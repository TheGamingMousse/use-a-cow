#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll hilbertorder(int x, int y) {
    const int logn = __lg(max(x, y) * 2 + 1) | 1;
    const ll maxn = (1ll << logn) - 1;
    ll res = 0;
    for (ll s = 1ll << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn;
            swap(x, y);
        }
    }
    return res;
}