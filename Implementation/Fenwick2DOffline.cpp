#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Offline 2D Fenwick Tree implementation.
 * Note that n needs to be of a reasonable size, and
 * all the updates/queries inputs are zero indexed.
 */
template <typename T> class OfflineFenwick2D {
  private:
    const int n;
    vector<vector<int>> vals;
    vector<vector<T>> arr;

    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

  public:
    OfflineFenwick2D(int _n, vector<array<int, 2>> &todo)
        : n(_n), vals(n + 1), arr(n + 1) {
        sort(begin(todo), end(todo), 
            [](const auto &a, const auto &b) -> bool {
            return a[1] < b[1];
        });
        for (int i = 1; i <= n; i++) { vals[i].push_back(0); }
        for (auto [r, c] : todo) {
            r++, c++;
            for (; r <= n; r += r & -r) {
                if (vals[r].back() != c) { vals[r].push_back(c); }
            }
        }
        for (int i = 1; i <= n; i++) {
            arr[i].resize(vals[i].size());
        }
    }

    /** adds val to the point (r, c) */
    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            int i = ind(vals[r], c);
            for (; i < arr[r].size(); i += i & -i) {
                arr[r][i] += val;
            }
        }
    }

    /** @return rectangle sum for corners (0, 0), (r, c) */
    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            int i = ind(vals[r], c);
            for (; i > 0; i -= i & -i) {
                sum += arr[r][i];
            }
        }
        return sum;
    }

    /** @return rectangle sum with corners (r1, c1) and (r2, c2) */
    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - 
               rect_sum(r1 - 1, c2) + rect_sum(r1 - 1, c1 - 1);
    }
};