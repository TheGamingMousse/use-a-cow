#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<class T> class FenwickTree {
    private:
        int sz; vector<T> arr;
    public:
        FenwickTree(int n) {
            sz = n + 1;
            arr.resize(n + 1);
        }
        FenwickTree() {} // empty init
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
            ++r, ++c; // r, c 0 indexed at first
            for (int i = r; i < n; i += i & -i) {
                for (int j = c; j < m; j += j & -j) {
                    arr[i][j] += dx;
                }
            }
        }
        T get(int r, int c) {
            T tot = 0; ++r, ++c;
            for (int i = r; i > 0; i -= i & -i) {
                for (int j = c; j > 0; j -= j & -j) {
                    tot += arr[i][j];
                }
            }
            return tot;
        }
        T query(int r1, int c1, int r2, int c2) {
            return get(r2, c2) - get(r2, c1) - 
                get(r1, c2) + get(r1, c1);
        }
};
/*
USACO Guide implementation.
Uses a template.
*/
// CP Algo Implementation
struct SegTree {
    vector<int> arr;
    SegTree(int n) {
        arr.resize(n * 4);
    }
    void build(vector<int>& a,
        int v, int tl, int tr) {
        if (tl == tr) {
            arr[v] = a[tl];
        } else {
            int m = (tl + tr) / 2;
            build(a, v * 2, tl, m);
            build(a, v * 2 + 1, m + 1, tr);
            arr[v] = arr[v * 2] + arr[v * 2] + 1;
        }
    }
    int query(int v, int tl, 
        int tr, int l, int r) {
        if (r < tl || l > tr) {
            // outside the range
            return 0;
        }
        if (l == tl && r == tr) {
            // completely contained
            return arr[v];
        }
        int m = (tl + tr) / 2;
        return query(v * 2, tl, m, l, min(r, m)) +
            query(v * 2 + 1, m + 1, tr, max(l, m + 1), r);
    }
    void update(int v, int l, int r, 
        int pos, int val) {
        if (l == r) {
            arr[v] = val;
        } else {
            int m = (l + r) / 2;
            if (pos <= m) {
                update(v * 2, l, m, pos, val);
            } else {
                update(v * 2 + 1, m + 1, r, pos, val);
            }
            arr[v] = arr[v * 2] +
                arr[v * 2 + 1];
        }
    }
};
/**
 * Modify the function according to
 * the query type. Currently is designed
 * for sum queries.
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
            idx += len;
            t[idx] = val;
            for (; idx > 1; idx >>= 1) {
                t[idx / 2] = join(t[idx], t[idx ^ 1]);
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
/*
 * Much shorter implementation.
 * Also iterative, but no lazy prop :c
*/