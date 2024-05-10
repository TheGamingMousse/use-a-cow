#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
/**
 * USACO.Guide implementation, with
 * my edits to make it look cleaner.
 * 
 * Also, if need be, you can also made it more modular...
*/
template<typename T> class FenwickTree {
    private:
        int n; vector<T> arr;
    public:
        FenwickTree(int _n) : n(_n + 1), arr(n) {}
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
 * Two dimentional Fenwick Tree.
*/
template<typename T> class FT2D {
    private:
        int n, m; vector<vector<T>> arr;
    public:
        FT2D(int _n, int _m) : n(_n), m(_m) {
            arr = vector(n, vector(m, (T) 0));
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
            return (get(r2, c2) + get(r1 - 1, c1 - 1) -
                    get(r1 - 1, c2) - get(r2, c1 - 1));
        }
};
/**
 * Sparse table, RMQ.
*/
template<class T> struct RMQ {
	const int n, LOG;
	const T DEF = numeric_limits<T>::max();
	vector<vector<T>> st;
	T join(T a, T b) { return min(a, b); }
	RMQ(int _n, vector<T> &v) : n(_n), LOG(__lg(n) + 1) {
		st = vector(LOG, vector(n, DEF));
		for (int i = 0; i < n; i++) {
			st[0][i] = v[i];
		}
		for (int i = 1; i < LOG; i++) {
			for (int j = 0; j + (1 << i) <= n; j++) {
				st[i][j] = join(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	T query(int l, int r) { // RMQ on [l, r]
		assert(l <= r);
		int i = __lg(r - l + 1);
		return join(st[i][l], st[i][r - (1 << i) + 1]);
	}
};
/**
 * The ai.cash segment tree, except I made 
 * it more generic... because I like templates!
*/
template <typename T> class SegmentTree {
    private:
        constexpr T DEF = {0, 0};
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree(vector<T> &arr) {
            len = (int) arr.size();
            t = vector<T>(len * 2, DEF);
            for (int i = 0; i < len; i++) {
                t[i + len] = arr[i];
            }
            for (int i = len - 1; i >= 1; i--) {
                t[i] = join(t[i << 1], t[i << 1 | 1]);
            }
        }
        SegmentTree() {}
        T join(T a, T b) { return max(a, b); } // any function
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
 * Brian's template!
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
    void forRange(int node_1, int node_2, F f) {
        for (; node_1 < node_2; node_1 >>= 1, node_2 >>= 1) {
            if (node_1 & 1) f(node_1++);
            if (node_2 & 1) f(--node_2);
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
    void forRangeOrdered(int node_1, int node_2, bool dir, F f) {
        int base = !dir ? node_1 - 1 : node_2;
        const int mask = (1 << log2((node_1 - 1) ^ node_2)) - 1;
        const int offset = !dir ? 1 : -1;
        int node = (!dir ? -node_1 : node_2) & mask;
        while (node) {
            const int bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }
        base = dir ? node_1 - 1 : node_2;
        node = (dir ? -node_1 : node_2) & mask;
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