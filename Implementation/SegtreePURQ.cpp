#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T> class SegmentTree {
    private:
        constexpr T DEF = {0, 0}; // change depending on T
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
        /** @return query on [l, r) */
        T qry(int l, int r) {
            T resl = DEF, resr = DEF;
            for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
                if (l & 1) { resl = join(resl, t[l++]); }
                if (r & 1) { resr = join(t[--r], resr); }
            }
            return join(resl, resr);
        }
        /** @return value at position idx */
        T get(int idx) {
            return t[idx + len];
        }
};