#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

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
void demo() {
    set<Demo1> st1; // valid
    set<Demo1, greater<Demo1>> std2; // valid
    set<Demo2, cmp> st3; // valid
    set<int, greater<int>> st4; // valid
    map<int, int, greater<int>> mp1; // valid
    priority_queue<Demo1> pq; // valid 
    priority_queue<int, vector<int>, greater<int>> pq1; // valid
}
struct Edge {
    int f, s, w, id;
};
bool operator<(const Edge& x, 
    const Edge& y) {
    return x.w > y.w;
}
// ^^ also valid
/*
Note: For custom sets,
the operator cannot use smth like
Demo1&!! Unless it's const Demo1&.
Also, lower bound needs an
object to be passed through...
obviously.
*/
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