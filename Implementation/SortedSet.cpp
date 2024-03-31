#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
struct Demo1 {
    int a, b, c;
    bool operator<(const Demo1& y) const {
        return c < y.c;
    }
};
struct Demo2 {
    int a, b, c;
};
struct cmp {
    bool operator()(const Demo1& x, const Demo1& y) const {
        return x.c < y.c;
    }
    bool operator()(const Demo2& x, const Demo2& y) const {
        return x.c < y.c;
    }
    // can add as many as you want b/c function overloading
};
struct hsh {
	size_t operator()(const pair<int, int> &p) const {
		return p.f * 239 + p.s;
	}
};
struct hsh {
	size_t operator()(const pii &p) const {
		return p.f * 239 + p.s;
	}
};
/**
 * For the upper two:
 * unordered_map<pii, T, hash>
*/
namespace std {
    template <> struct hash<pii> {
        size_t operator()(const pii &p) const { 
            return p.f * 239 + p.s; 
        }
    };
}
/**
 * For this, you can just do
 * unordered_map<pii, int>.
*/