#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    vector<int> e;
    DisjointSet(int n) { e = vector<int>(n, -1); }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};