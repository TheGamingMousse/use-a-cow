#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * USACO.Guide implementation, with
 * my edits to make it look cleaner.
*/
template<typename T> class FenwickTree {
    private:
        int n; vector<T> arr;
    public:
        FenwickTree(int _n) : n(_n + 1) {
            arr.resize(n);
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
            for (++idx; idx < n; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
/**
 * Two dimentional Fenwick Tree. Shout out
 * to mudkip for the implementation :)
 * (This is really scuffed... ima clean it up sometime.)
*/
template<typename T> class FT2D {
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
template <typename T> class SegmentTree {
    private:
        const T DEF = 0;
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree() {}
        T join(T a, T b) { // any arbitrary function
            return max(a, b);
        }
        void set(int idx, T val) { 
            for (t[idx += len] = val; idx >>= 1; ) {
                t[idx] = join(t[idx << 1], t[idx << 1 | 1]);
            }
        }
        T query(int l, int r) { // queries [l, r)
            T resl = DEF, resr = DEF;
            for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
                if (l & 1) resl = join(resl, t[l++]);
                if (r & 1) resr = join(t[--r], resr);
            }
            return join(resl, resr);
        }
        T get(int idx) {
            return t[idx + len];
        }
};
/**
 * A lazy segment tree. Yoinked from a certain
 * CF GM lol.
*/
template<typename T, typename U> 
struct LazySegtree {
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
    template<class F> void push(int l, int r, int v, F toChild) {
        // pushes v's lazy value to children
        int m = (l + r) >> 1;
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
    template<class F> void update(int ql, int qr, T x, F st) {
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
    int forLevels(int node, int sz, bool dir, F f) {
        while (node < sz) {
            node = node << 1 | dir + (!dir ? f(node) : -f(node));
        }
        return node;
    }
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
    template<typename F> 
    void forParents(int p, bool dir, F f) {
        const int lvls = log2(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    template<typename F> 
    void forRangeOrdered(int lf, int rt, bool dir, F f) {
        auto base = !dir ? lf - 1 : rt;
        const int mask = (1 << log2((lf - 1) ^ rt)) - 1;
        const int offset = !dir ? 1 : -1;
        int node = (!dir ? -lf : rt) & mask;
        while (node) {
            const int bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }
        base = dir ? lf - 1 : rt;
        node = (dir ? -lf : rt) & mask;
        while (node) {
            const int bit = log2(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }
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