#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
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
    for (int i = 0; i < 30; i++) { // arbitrary
        double mid = (low + high) / 2;
        fn(mid) ? high = mid : low = mid;
    }
    return low;
}
template<typename F>
double decimalLastTrue(double low, double high, F fn) {
    for (int i = 0; i < 30; i++) { // arbitrary
        double mid = (low + high) / 2;
        fn(mid) ? low = mid : high = mid;
    }
    return low;
}