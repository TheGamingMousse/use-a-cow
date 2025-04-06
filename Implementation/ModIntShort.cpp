#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<int MOD> struct MInt {
    int v; 
    constexpr MInt() : v(0) {}
    constexpr MInt(ll _v) : v (int(_v % MOD)) { v += (v < 0) * MOD; }
    explicit operator int() const { return v; } 
    MInt& operator+=(MInt o) { if ((v += o.v) >= MOD) { v -= MOD; } return *this; }
    MInt& operator-=(MInt o) { if ((v -= o.v) < 0) { v += MOD; } return *this; }
    MInt& operator*=(MInt o) { v = int((ll) v * o.v % MOD); return *this; }
    MInt& operator/=(MInt o) { *this *= inv(o); return *this; }
    friend MInt modpow(MInt a, ll p) { return p ? modpow(a * a, p / 2) * (p & 1 ? a : 1) : 1; }
    friend MInt inv(MInt o) { return modpow(o, MOD - 2); }
    friend MInt operator+(MInt a, MInt b) { return a += b; }
    friend MInt operator-(MInt a, MInt b) { return a -= b; }
    friend MInt operator*(MInt a, MInt b) { return a *= b; }
    friend MInt operator/(MInt a, MInt b) { return a /= b; }
};