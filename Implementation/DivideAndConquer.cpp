#include <bits/stdc++.h>
using namespace std;

void merge(int l, int r,
    vector<int>& arr) {
    vector<int> temp;
    int mid = (l + r) / 2,
        i = l, j = mid;
    while (i < mid && j < r) {
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
            ++i;
        } else {
            temp.push_back(arr[j]);
            ++j;
        }
    }
    while (i < mid) {
        temp.push_back(arr[i]);
        ++i;
    }
    while (j < r) {
        temp.push_back(arr[j]);
        ++j;
    }
    for (int i = 0; i < size(temp); i++) {
        arr[l + i] = temp[i];
    }
}
void sort(int l, int r, 
    vector<int>& arr) {
    if (l == r) return;
    int mid = (l + r) / 2;
    sort(l, mid, arr);
    sort(mid, r, arr);
    merge(l, r, arr);
}
/*
Merge sort implementation.
Recurrence is T(n) = n + 2T(n / 2),
so time complexity is O(NlogN)
*/
int cnt(int l, int r, 
    vector<int>& arr) {
    int mid = (l + r) / 2,
        res = 0, j = mid;
    for (int i = l; i < mid; i++) {
        while (j < r && arr[i] 
            > arr[j] * 2) {
            ++j;
        }
        res += j - mid;
    }
    return res;
}
int pairs(int l, int r,
    vector<int>& arr) {
    if (l == r - 1) return 0;
    int mid = (l + r) / 2,
        res = 0;
    res = pairs(l, mid, arr)
        + pairs(mid, r, arr)
        + cnt(l, r, arr);
    merge(l, r, arr);
    return res;
}
/*
Reverse pairs/inversions implementation.
^ Counting inversions can be solved
in a similar way
Uses divide & conquer + 
merge sort to do its thing.
*/