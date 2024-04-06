#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 
 
template<class T> bool smin(T& a, T b) {
    return (b < a ? a = b, 1 : 0);
}
template<class T> bool smax(T& a, T b) {
    return (b > a ? a = b, 1 : 0);
}
template<int MOD> struct MInt {
 	explicit operator int() const { return v; } 
    int v;
	MInt() : v(0) {}
	MInt(ll _v) : v (int(_v % MOD)) { v += (v < 0) * MOD; }
	MInt& operator+=(MInt o) { 
		if ((v += o.v) >= MOD) v -= MOD; 
		return *this; 
    }
	MInt& operator-=(MInt o) { 
		if ((v -= o.v) < 0) v += MOD; 
		return *this; 
    }
	MInt& operator*=(MInt o) { 
		v = int((ll) v * o.v % MOD); 
        return *this; 
    }
    MInt& operator/=(MInt o) {
        v = v * inv(o);
        return *this;
    }
	friend MInt modpow(MInt a, ll p) {
        MInt res = 1;
        for (; p; p >>= 1, a = a * a) {
            if (p & 1) res = res * a;
        }
        return res;
    }
	friend MInt inv(MInt a) { return modpow(a, MOD - 2); }
	friend MInt operator+(MInt a, MInt b) { return a += b; }
	friend MInt operator-(MInt a, MInt b) { return a -= b; }
	friend MInt operator*(MInt a, MInt b) { return a *= b; }
    friend MInt operator/(MInt a, MInt b) { return a /= b; }
};
template<typename T> class Combinatorics {
    // T = MInt<Modulo>, for obvious reasons.
    private:
        vector<T> fact, invFact;
        int ptr = 0;
    public:
        Combinatorics() {}
        Combinatorics(int n) { reserve(n); }
        void reserve(int size) {
            if (ptr == 0) {
                fact.emplace_back(1);
                invFact.emplace_back(1);
                ptr = 1;
            }
            if (size < ptr) continue;
            fact = vector<T>(size + 1);
            invFact = vector<T>(size + 1);
            for (int i = ptr; i <= size; i++) {
                fact[i] = fact[i - 1] * T(i);
            }
            invFact[size] = T(1) / fact[size];
            for (int i = size - 1; i >= ptr; i--) {
                invFact[i] = invFact[i + 1] * T(i + 1);
            }
            ptr = size + 1;
        }
        T combine(int n, int k) { 
            assert(n >= k), reserve(n);
            return fact[n] * invFact[k] * invFact[n - k]; 
        }
        T permute(int n, int k) { 
            assert(n >= k), reserve(n); 
            return fact[n] * invFact[n - k];
        }
        T getInv(int n) { reserve(n); return invFact[n] * fact[n - 1]; }
        T getInvFact(int n) { reserve(n); return invFact[n]; }
        T getFact(int n) { reserve(n); return fact[n]; }
};
/**
 * Use the following for USACO, b/c fat template
 * is kind of suspect
*/
const int MOD = 1e9 + 7;
const int N = 2e6 + 1;
ll fact[N], invFact[N];
ll expo(ll x, ll n, ll m = MOD) {
    ll res = 1; x %= m;
    for (; n; n >>= 1, x = (x * x) % m) {
        if (n & 1) res = (res * x) % m;
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
void init() {
    fact[0] = 1, invFact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}