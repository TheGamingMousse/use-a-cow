#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * Segtree template that I think is generic enough.
 * Note that I haven't figured out how to support range
 * set as well lol.
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
        // set yourself
        // applies the update x to node v.
    }
    void push(int l, int r, int v) {
        if (lz[v] != LZ_ID && l != r) {
            int m = (l + r) >> 1;
            for (int x : {2 * v, 2 * v + 1}) {
                int len = (x == 2 * v ? m - l + 1 : r - m);
                apply(x, len, lz[v]);
            }
        }
        lz[v] = LZ_ID;
    }
    void upd(int ql, int qr, U x, int l, int r, int v) {
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr) {
            apply(v, r - l + 1, x);
        } else {
            push(l, r, v);
            int m = l + r >> 1;
            upd(ql, qr, x, l, m, v * 2);
            upd(ql, qr, x, m + 1, r, v * 2 + 1);
            t[v] = comb(t[v * 2], t[v * 2 + 1]);
        }
    }
    void upd(int ql, int qr, U x) {
        return upd(ql, qr, x, 0, sz - 1, 1);
    }
    T qry(int ql, int qr, int l, int r, int v) {
        if (qr < l || ql > r) return ID;
        if (l >= ql && r <= qr) return t[v];
        push(l, r, v);
        int m = (l + r) >> 1;
        return comb(qry(ql, qr, l, m, v * 2), qry(ql, qr, m + 1, r, v * 2 + 1));
    }
    T qry(int ql, int qr) {
        return qry(ql, qr, 0, sz - 1, 1);
    }
};