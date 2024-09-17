#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * Binary search template.
 * NOTE: If there is no value in the range that
 * satisfies the function, it returns an endpoint.
 * Make sure to account for this.
*/
template <typename T, typename F> 
T first_true(T low, T high, const F &fn) {
    while (low < high) {
        T mid = low + (high - low) / 2;
        fn(mid) ? high = mid : low = mid + 1;
    }
    return low;
}
template <typename T, typename F> 
T last_true(T low, T high, const F &fn) {
    while (low < high) {
        T mid = low + (high - low + 1) / 2;
        fn(mid) ? low = mid : high = mid - 1;
    }
    return low;
}
