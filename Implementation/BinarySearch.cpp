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
/**
 * binarySearch1: finding the lowest "true"
 * Example: {0, 0, 1, 1, 1}
 * Output: 2
 * binarySearch2: finding the highest "true"
 * Example: {1, 1, 1, 0, 0}
 * Output: 2
 * 
 * Note: Need to write a decimal binary search.
*/