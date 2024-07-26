#include <bits/stdc++.h>
using namespace std;

/**
 * Verified with Yosupo.
*/
struct DisjointSet {
    vector<int> e;
    DisjointSet(int n) : e(n, -1) {}
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool same_set(int x, int y) { return get(x) == get(y); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};