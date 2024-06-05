#include <bits/stdc++.h>
using namespace std;

/**
 * Verified with CSES (Dynamic RMQ)
 * Define a join function, and then your declaration
 * would be something like:
 * 
 * SegmentTree<T, DEF_VAL, decltype(join)> segtree(arr, join)
*/
template<class T, T DEF, class F> class SegmentTree {
    private:
        int len; F join; vector<T> t; 
    public:
        SegmentTree() {}
        SegmentTree(vector<T> &arr, F fn) : join(fn) {
            len = (int) arr.size();
            t = vector<T>(len * 2, DEF);
            for (int i = 0; i < len; i++) {
                t[i + len] = arr[i];
            }
            for (int i = len - 1; i >= 1; i--) {
                t[i] = join(t[i << 1], t[i << 1 | 1]);
            }
        }
        void set(int idx, T val) {
            for (t[idx += len] = val; idx >>= 1; ) {
                t[idx] = join(t[idx << 1], t[idx << 1 | 1]);
            }
        }
        /** @return query on [l, r) */
        T query(int l, int r) {
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