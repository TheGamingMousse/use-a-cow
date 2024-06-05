#include <bits/stdc++.h>
using namespace std;

template<class T> struct RMQ {
    int n, log2dist;
    vector<vector<T>> st;
    int lvl(int x) { return 31 - __builtin_clz(x); }
    void init(vector<T> &v) {
        n = static_cast<int>(v.size());
        log2dist = lvl(n) + 1;
        st.resize(log2dist);
        st[0] = v;
        for (int i = 1; i < log2dist; i++) {
            st[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    /** @return minimum on [l, r] */
    T query(int l, int r) {
        int i = lvl(r - l + 1);
        return min(st[i][l], st[i][r - (1 << i) + 1]);
    }
};