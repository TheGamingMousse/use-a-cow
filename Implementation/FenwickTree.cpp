#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> struct FenwickTree {
    const int n; 
    vector<T> arr;
    FenwickTree(int _n) : n(_n + 1), arr(n) {}

    /** @return sum on [0, idx] */
    T pre(int idx) {
        T tot = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            tot += arr[idx];
        }
        return tot;
    }

    /** changes the location at idx by dx */
    void upd(int idx, T dx) {
        for (++idx; idx < n; idx += idx & -idx) {
            arr[idx] += dx;
        }
    }

    /** @return sum on [l, r] */
    T qry(int l, int r) { return pre(r) - pre(l - 1); }

    /** @return first index i with pre(i) >= x */
    int lower_bound(T x) {
        T sum = 0;
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) < n && sum + arr[pos + (1 << i)] < x) {
                sum += arr[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos;
    }
};