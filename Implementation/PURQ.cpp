#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * USACO.Guide implementation, with
 * my edits to make it look cleaner.
*/
template<class T> class FenwickTree {
    private:
        int sz; vector<T> arr;
    public:
        FenwickTree(int n) {
            sz = n + 1, arr.resize(n + 1);
        }
        T prefix(int idx) { // [0, idx] sum
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) { // [l, r] sum
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < sz; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
/**
 * Two dimentional Fenwick Tree. Shout out
 * to mudkip for the implementation :)
*/
template<class T> class FT2D {
    private:
        int n, m;
        vector<vector<T>> arr;
    public:
        FT2D(int N, int M) {
            n = N + 1;
            m = M + 1;
            arr = vector<vector<T>>(N + 1, 
                vector<T>(M + 1));
        }
        void update(int r, int c, T dx) {
            for (int i = r + 1; i < n; i += i & -i) {
                for (int j = c + 1; j < m; j += j & -j) {
                    arr[i][j] += dx;
                }
            }
        }
        T get(int r, int c) {
            T tot = 0;
            for (int i = r + 1; i > 0; i -= i & -i) {
                for (int j = c + 1; j > 0; j -= j & -j) {
                    tot += arr[i][j];
                }
            }
            return tot;
        }
        T query(int r1, int c1, int r2, int c2) {
            return get(r2, c2) - get(r2, c1) - 
                   get(r1, c2) + get(r1, c1);
            // note... this might be sketch hahahaha
        }
};
/**
 * The ai.cash segment tree, except I made 
 * it more generic... because I like templates!
*/
template <class T> class SegmentTree {
    private:
        const T DEF = 0;
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree() {} // empty init
        T join(T a, T b) {
            return max(a, b);
        }
        void set(int idx, T val) {
            t[idx += len] = val;
            for (; idx > 1; idx >>= 1) {
                t[idx >> 1] = join(t[idx], t[idx ^ 1]);
            }
        }
        T query(int l, int r) { // queries [l, r)
            T res = DEF;
            for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = join(res, t[l++]);
                if (r & 1) res = join(res, t[--r]);
            }
            return res;
        }
        T get(int idx) {
            return query(idx, idx + 1);
        }
};
/**
 * A lazy segment tree. Yoinked from a certain
 * CF GM lol.
*/
template<class T, class U> struct LazySegtree {
    static constexpr T ID = 0;
    static constexpr U LZ_ID = 0;
    int sz = 0; 
    vector<T> t = vector<T>();
    vector<U> lz = vector<U>();
    inline T join(T a, T b) { return a + b; }
    // join is just any arbitrary function.
    void init(int _sz) {
        sz = _sz;
        t.assign(sz * 4, val);
        lz.assign(sz * 4, LZ_ID);
    }
    void init(vector<T> &a) {
        sz = a.size();
        t.resize(sz * 4);
        lz.assign(sz * 4, LZ_ID);
        build(0, sz - 1, 1, a);
    }
    void build(int l, int r, int v, vector<T> &a) {
        if (l == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) >> 1;
            build(l, m, v * 2, a);
            build(m + 1, r, v * 2 + 1, a);
            t[v] = join(t[v * 2], t[v * 2 + 1]);
        }
    }
    inline void push(int l, int r, int v) {
        // pushes v's lazy value to children
        int m = (l + r) >> 1;
        auto toChild = [&](int pr, int ch, int len) -> void {
            // DIY, pushes pr's lazy to ch's lazy.
        };
        if (lz[v] != LZ_ID && l != r) {
            toChild(v, v * 2, m - l + 1);
            toChild(v, v * 2 + 1, r - m);
        }
        lz[v] = LZ_ID;
    }
    template<class F> void upd(int ql, int qr, int l, int r,
                               int v, T x, F set) {
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr) {
            set(v, l, r);
        } else {
            push(l, r, v);
            int m = (l + r) >> 1;
            upd(ql, qr, l, m, v * 2, x, set);
            upd(ql, qr, m + 1, r, v * 2 + 1, x, set);
            t[v] = join(t[v * 2], t[v * 2 + 1]);
        }
    }
    void update(int ql, int qr, T x) {
        auto st = [&](int cv, int cl, int cr) -> void {
            // apply update to cv, set lazy update at cv.
        };
        upd(ql, qr, 0, sz - 1, 1, x, st);
    }
    T query(int ql, int qr, int l, int r, int v) {
        if (qr < l || ql > r) return ID;
        if (l >= ql && r <= qr) return t[v];
        push(l, r, v);
        int m = (l + r) >> 1;
        T lf = query(ql, qr, l, m, v * 2);
        T rt = query(ql, qr, m + 1, r, v * 2 + 1);
        return join(lf, rt);
    }
    T query(int ql, int qr) {
        return query(ql, qr, 0, sz - 1, 1);
    }
};
/**
 * Brian's template... removed some methods tho.
*/
namespace SegmentTree {
    template <typename F>
    void forRange(int lf, int rt, F f) {
        for (; lf < rt; lf >>= 1, rt >>= 1) {
            if (lf & 1) f(lf++);
            if (rt & 1) f(--rt);
        }
    } 
    int log2(int x) {
        return 31 - __builtin_clz(x);
    }
    template <typename F>
    void forParents(int p, bool dir, F f) {
        const auto lvls = log2(p);
        for (auto i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    template<class T, class U>
    void update(int l, int r, T apply, U pull) {
        forRange(l, r, apply);
        forParents(l, true, pull);
        forParents(r - 1, true, pull);
    }
    template<class T, class U>
    void query(int l, int r, T push, U apply) {
        forParents(l, false, push);
        forParents(r - 1, false, push);
        forRange(l, r, apply);
    }
}
/**
 * To do updates:
 * Write a lambda that applies an update to each node
 * that is used, and then sets a lazy value. Then,
 * use forParents to go upwards and essentially rebuild
 * the tree along the path used.
 * 
 * To do queries:
 * First, use forParents to push all the updates downwards.
 * Then, use forRange to do the updates.
*/