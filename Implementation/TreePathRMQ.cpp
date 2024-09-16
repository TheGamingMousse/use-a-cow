#include <bits/stdc++.h>
using namespace std;

/**
 * Answers tree path RMQ in O(log n).
 * Uses merging by size but does
 * not use path compression.
 */
constexpr int INF = 1e9 + 7;
struct DisjointSet {
    vector<int> e, t;
    DisjointSet(int n) { 
        e = vector<int>(n, -1); 
        t = vector<int>(n, INF);
    }
    int get(int x) { return e[x] < 0 ? x : get(e[x]); }
    bool unite(int x, int y, int w) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x, t[y] = w;
        return true;
    }
    int ask(int x, int y) {
        int res = 0;
        while (x != y) {
            if (t[x] > t[y]) swap(x, y);
            res = t[x], x = e[x];
        }
        return res;
    }
};