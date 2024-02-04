#include <bits/stdc++.h>
using namespace std;

int firstTrue(function<bool(int)> check) {
    int low = 0, high = 1e5; // arbitrary
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}
int lastTrue(function<bool(int)> check) {
    int low = 0, high = 1e5; // arbitrary
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    return low;
}
double binarySearch3(function<bool(double)> check) {
    double low = 0, high = 1e5, prec = 1e-5; // arbitrary
    while (high - low > prec) {
        double mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
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
 * Note: for more finnicky probs, use the 
 * bisearch detailed in "The Meeting Place
 * Cannot Be Changed".
*/