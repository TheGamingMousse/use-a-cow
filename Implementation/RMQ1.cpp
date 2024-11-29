#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * <O(n log n), O(1)> RMQ implementation. Some stuff is
 * borrowed from tourist.
*/
template <class T> struct RMQ {
    int n; 
    vector<vector<T>> st;
    
    void init(const vector<T> &a) {
        n = (int) a.size();
        int max_log = 1 + __lg(n);
        st.resize(max_log);
        st[0] = a;
        for (int j = 1; j < max_log; j++) {
            st[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    /** @return query on range [l, r] */
    T qry(int l, int r) const {
        int lg = __lg(r - l + 1);
        return min(st[lg][l], st[lg][r - (1 << lg) + 1]);
    }
};