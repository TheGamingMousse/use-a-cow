#include <bits/stdc++.h>
using namespace std;

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