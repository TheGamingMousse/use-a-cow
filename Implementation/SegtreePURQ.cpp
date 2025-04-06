#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Verified with CSES (Dynamic RMQ)
 * Define a join function, and then your declaration
 * would be something like:
 * 
 * SegmentTree st(arr, join, def)
*/
template <typename T, typename F> 
class SegmentTree {
  private:
    const int len; 
    const T DEF; 
    const F join; 
    vector<T> t; 
    
  public:
    SegmentTree() {}
    SegmentTree(const vector<T> &arr, T val, const F &fn) 
        : len(arr.size()), DEF(val), join(fn) {
        t = vector<T>(len * 2, DEF);
        for (int i = 0; i < len; i++) {
            t[i + len] = arr[i];
        }
        for (int i = len - 1; i > 0; i--) {
            t[i] = join(t[i << 1], t[i << 1 | 1]);
        }
    }

    void set(int idx, T val) {
        for (t[idx += len] = val; idx >>= 1; ) {
            t[idx] = join(t[idx << 1], t[idx << 1 | 1]);
        }
    }

    /** @return query on [l, r) */
    T qry(int l, int r) {
        T res_l = DEF, res_r = DEF;
        for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { res_l = join(res_l, t[l++]); }
            if (r & 1) { res_r = join(t[--r], res_r); }
        }
        return join(res_l, res_r);
    }
    
    /** @return value at location idx */
    T get(int idx) {
        return t[idx + len];
    }
};