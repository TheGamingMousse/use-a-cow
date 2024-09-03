#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * How to use: set the ID and LZ_ID accordingly.
 * Also, write the apply function accordingly. 
 * That's basically it! You might need to write some
 * diff code for the build and segtree walking though, depending
 * on your use case.
 */
// T = tree node type, which will be long long
// U = update type, which will be array<ll, 2>
template<class T, class U> struct LazySegtree {
    static constexpr T ID = 0;         // neutral tree node value
    static constexpr U LZ_ID = {0, 0}; // neutral lazy update value
    const int sz;
    vector<T> t;
    vector<U> lz;
 
    inline T comb(T a, T b) { return a + b; }
    void init(vector<T> &a) {
        sz = a.size();
        t.resize(sz * 4, ID);
        lz.assign(sz * 4, LZ_ID);
        build(0, sz - 1, 1, a);
    }
    LazySegtree(const vector<T> &a)
        : sz((int) a.size()), t(4 * sz, ID), lz(4 * sz, LZ_ID) {
        build(1, 0, sz - 1, a);
    }   
    void build(int v, int l, int r, const vector<T> &a) {
        if (l == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) >> 1;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            t[v] = comb(t[2 * v], t[2 * v + 1]);
        }
    }
    void apply(int v, int len, U x) {
        // applies lazy update to v, 
        // sets lazy update to lz[v]
    }
    void pushdown(int v, int l, int r) {
        if (lz[v] != LZ_ID && l != r) {
            int m = (l + r) >> 1;
            apply(2 * v, m - l + 1, lz[v]);
            apply(2 * v + 1, r - m, lz[v]);
        }
        lz[v] = LZ_ID;
    }
    void upd(int v, int l, int r, int ql, int qr, U x) {
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) >> 1;
            upd(2 * v, l, m, ql, qr, x);
            upd(2 * v + 1, m + 1, r, ql, qr, x);
            t[v] = comb(t[2 * v], t[2 * v + 1]);
        }
    }
    void upd(int ql, int qr, U x) {
        upd(1, 0, sz - 1, ql, qr, x);
    }
    T qry(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return ID;
        if (l >= ql && r <= qr) return t[v];
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        return comb(qry(2 * v, l, m, ql, qr), 
                    qry(2 * v + 1, m + 1, r, ql, qr));
    }
    T qry(int ql, int qr) {
        return qry(1, 0, sz - 1, ql, qr);
    }
    template<class F> 
    int walk(int v, int l, int r, T cur, const F &func) {
        if (l == r) {
            return l;
        } else {
            int m = (l + r) / 2;
            pushdown(v, l, r);
            T x = comb(cur, t[2 * v]);
            return func(x) ? walk(2 * v, l, m, cur, func) 
                           : walk(2 * v + 1, m + 1, r, x, func);
        }
    }
    template<class F>
    int walk(const F &func) {
        return walk(1, 0, sz - 1, ID, func);
    }
};