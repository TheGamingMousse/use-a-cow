#include <bits/stdc++.h>
using namespace std;

/**
 * firstTrue and lastTrue verified,
 * decimalFirstTrue and decimalLastTrue
 * not verified yet (but they should work)
*/
template<typename F> 
int firstTrue(int low, int high, F fn) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        fn(mid) ? high = mid : low = mid + 1;
    }
    return low;
}
template<typename F> 
int lastTrue(int low, int high, F fn) {
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        fn(mid) ? low = mid : high = mid - 1;
    }
    return low;
}
template<typename F>
double decimalFirstTrue(double low, double high, F fn) {
    for (int i = 0; i < 60; i++) { // arbitrary
        double mid = (low + high) / 2;
        fn(mid) ? high = mid : low = mid;
    }
    return low;
}
template<typename F>
double decimalLastTrue(double low, double high, F fn) {
    for (int i = 0; i < 60; i++) { // arbitrary
        double mid = (low + high) / 2;
        fn(mid) ? low = mid : high = mid;
    }
    return low;
}