#include <bits/stdc++.h>
using namespace std;

template<typename T> class FenwickTree {
    private:
        int n; vector<T> arr;
    public:
        FenwickTree(int _n) : n(_n + 1), arr(n) {}
        /** @return sum on [0, idx] */
        T prefix(int idx) {
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        /** @return sum on [l, r] */
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        /** changes the location at idx by dx */
        void update(int idx, T dx) {
            for (++idx; idx < n; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};