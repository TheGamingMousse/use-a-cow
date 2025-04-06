#include <bits/stdc++.h>

using ll = long long;

#include "ModInt.cpp"

constexpr int MOD = 1e9 + 7;
using Z = MInt<MOD>;

namespace Combo {
    std::vector<Z> fact, inv;

    void init(int n) {
        fact.resize(n + 1);
        inv.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        inv[n] = 1 / fact[n];
        for (int i = n; i >= 1; i--) {
            inv[i - 1] = inv[i] * i;
        }
    }

    Z nck(int n, int k) {
        if (k > n || k < 0) { return 0; }
        return fact[n] * inv[k] * inv[n - k];
    }

    Z perm(int n, int k) {
        if (k > n || k < 0) { return 0; }
        return fact[n] * inv[n - k];
    }
}