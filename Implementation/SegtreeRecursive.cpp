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
template<class T, class U> struct LazySegtree {
    static constexpr T ID = 0;         // set yourself
    static constexpr U LZ_ID = {1, 0}; // set yourself
    int sz;
    vector<T> t;
    vector<U> lz;
 
    inline T comb(T a, T b) { return a + b; } // set yourself
    void init(int _sz, T val = ID) {
        sz = _sz;
        t.assign(sz * 4, val);
        lz.assign(sz * 4, LZ_ID);
    }
    void init(vector<T> &a) {
        sz = a.size();
        t.resize(sz * 4, ID);
        lz.assign(sz * 4, LZ_ID);
        build(0, sz - 1, 1, a);
    }
    void build(int l, int r, int v, vector<T> &a) {
        if (l == r)
            t[v] = a[l];
        else {
            int m = (l + r) >> 1;
            build(l, m, v * 2, a);
            build(m + 1, r, v * 2 + 1, a);
            t[v] = comb(t[v * 2], t[v * 2 + 1]);
        }
    }
    void apply(int v, int len, U x) {
        // apply the update x to node v
        // put the lazy update to lz[v]
    }
    void pushdown(int v, int l, int r) {
        if (lz[v] != LZ_ID && l != r) {
            int m = (l + r) / 2;
            for (int x : {2 * v, 2 * v + 1}) {
                int len = (x == 2 * v ? m - l + 1 : r - m);
                apply(x, len, lz[v]);
            }
        }
        lz[v] = LZ_ID;
    }
    void upd(int v, int l, int r, int ql, int qr, U x) {
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) / 2;
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
    template<class F> int walk(int v, int l, int r, F &func) {
        if (l == r) {
            return l;
        } else {
            pushdown(v, l, r);
            int m = (l + r) >> 1;
            return func(t[v * 2]) ? walk(2 * v, l, m, func)
                                  : walk(2 * v + 1, m + 1, r, func); 
        }
    }
    template<class F> int walk(F func) {
        return walk(1, 0, sz - 1, func);
    }
};