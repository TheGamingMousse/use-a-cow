#include <bits/stdc++.h>
using namespace std;

int binarySearch1(vector<bool>& check) {
    int low = 0, high = check.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check[mid]) high = mid;
        else low = mid + 1;
    }
}
int binarySearch2(vector<bool>& check) {
    int low = 0, high = check.size() - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check[mid]) low = mid;
        else high = mid - 1;
    }
}
int binarySearch3(function<bool(double)> check) {
    double low = 0, high = 1e5, precision = 1e-5;
    while (high - low > precision) {
        double mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << low << "\n";
}
/*
binarySearch1: finding the lowest "true"
Example: {0, 0, 1, 1, 1}
Output: 2
binarySearch2: finding the highest "true"
Example: {1, 1, 1, 0, 0}
Output: 2

Note: for more finnicky probs, use the 
bisearch detailed in "The Meeting Place
Cannot Be Changed".
*/