#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

void preprocess(vector<vector<int>>& up, 
    vector<pair<int, int>>& edges) {
    int LOG = up.size() - 1, n = up[0].size() - 1;
    for (auto i : edges) {
        up[0][max(i.f, i.s)] = min(i.f, i.s);
    }
    for (int i = 1; i <= LOG; i++) {
        for (int j = 1; j <= n; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
}
int jump(int x, int d, vector<vector<int>>& up) {
    int LOG = up.size() - 1;
    for (int i = LOG; i >= 0; i--) {
        if (d & (1 << i)) x = up[i][x];
    }
    return x;
}
/*
Preprocess function computes 
predecessors in powers of two.
O(NlogN)

Jump function breaks up the predecessor
number and uses binary to query.
O(logN)
*/