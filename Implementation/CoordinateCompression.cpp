#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

vector<vector<int>> coordinateCompression(
    vector<pair<pair<int, int>, int>>& locs) {
    int n = locs.size();
    vector<vector<int>> grid(n, vector<int>(n));
    vector<pair<int, int>> comp(n);
    sort(begin(locs), end(locs), [&](auto& x, auto& y) {
        return x.f.f < y.f.f;
    });
    for (int i = 0; i < n; i++) {
        comp[locs[i].s].f = i;
    }
    sort(begin(locs), end(locs), [&](auto x, auto y) {
        return x.f.s < y.f.s;
    });
    for (int i = 0; i < n; i++) {
        comp[locs[i].s].s = i;
    }
    for (const auto& i : comp) {
        grid[i.f][i.s] = 1;
    }
    return grid;
}
/*
Main idea is you sort
pair array, reassign vals,
blah blah blah.
O(NlogN)
*/