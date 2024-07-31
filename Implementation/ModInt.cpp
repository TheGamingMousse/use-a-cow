#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * Solves the equation ax + by = gcd(a, b).
 * Returns {gcd(a, b), x, y}.
 */
template<class T> array<T, 3> extendedGCD(T m, T n) {
    T a = 1, a_in = 0, b = 0, b_in = 1;
    while (n) {
        const T q = m / n;
        a_in = exchange(a, a_in) - q * a_in;
        b_in = exchange(b, b_in) - q * b_in;
        n = exchange(m, n) - q * n;
    }
    return array<T, 3>({m, a, b});
}
template<int MOD> struct MInt {
    int v; 
    MInt() : v(0) {}
    MInt(ll _v) : v (int(_v % MOD)) { v += (v < 0) * MOD; }
    explicit operator int() const { return v; } 
    MInt operator-() {
        return MInt(-v);
    }
    MInt& operator+=(MInt o) { 
        if ((v += o.v) >= MOD) { v -= MOD; }
        return *this; 
    }
    MInt& operator-=(MInt o) { 
        if ((v -= o.v) < 0) { v += MOD; }
        return *this; 
    }
    MInt& operator*=(MInt o) { 
        v = int((ll) v * o.v % MOD); 
        return *this; 
    }
    MInt& operator/=(MInt o) {
        *this *= MInt(extendedGCD(o.v, MOD)[1]);
        return *this;
    }
    friend MInt modpow(MInt a, ll p) {
        MInt res = 1;
        for (; p; p >>= 1, a *= a) {
            if (p & 1) res *= a;
        }
        return res;
    }
    friend MInt inv(MInt a) { return modpow(a, MOD - 2); }
    friend MInt operator+(MInt a, MInt b) { return a += b; }
    friend MInt operator-(MInt a, MInt b) { return a -= b; }
    friend MInt operator*(MInt a, MInt b) { return a *= b; }
    friend MInt operator/(MInt a, MInt b) { return a /= b; }
    friend ostream& operator<<(ostream &out, const MInt &n) { 
        return out << int(n); 
    }
    friend istream& operator>>(istream &in, MInt &n) { 
        long long _v; in >> _v, n = MInt(_v); return in; 
    }
};