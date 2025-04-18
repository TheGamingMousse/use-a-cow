#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T, typename F> 
struct SparseTable {
    const int n; 
    const F join;
    vector<vector<T>> st;
    
    SparseTable(const vector<T> &a, const F &f) 
               : n(a.size()), join(f) {
        int max_log = 1 + __lg(n);
        st.resize(max_log);
        st[0] = a;
        for (int j = 1; j < max_log; j++) {
            st[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                st[j][i] = join(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    /** @return query on range [l, r] */
    T qry(int l, int r) const {
        int lg = __lg(r - l + 1);
        return join(st[lg][l], st[lg][r - (1 << lg) + 1]);
    }
};