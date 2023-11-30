#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void calc1D(vector<ll>& pf) {
    for (int i = 1; i < pf.size(); i++) {
        pf[i] += pf[i - 1];
    }
}
void calc2D(vector<vector<ll>>& pf) {
    for (int i = 1; i < pf.size(); i++) {
        for (int j = 1; j < pf[i].size(); j++) {
            pf[i][j] += pf[i - 1][j] + pf[i][j - 1]
                - pf[i - 1][j - 1];
        }
    }
}
ll calcArea(int r1, int c1, int r2, int c2, 
    vector<vector<ll>>& pf) {
    return pf[r2][c2] - pf[r1 - 1][c2]
        - pf[r2][c1 - 1] + pf[r1 - 1][c1 - 1];
}
ll kadanes1D(vector<ll>& arr) {
    ll best = LONG_LONG_MIN, cur = 0;
    for (ll i : arr) {
        cur += i;
        best = max(best, cur);
        cur = max(cur, (ll) 0);
    }
    return best;
}
ll kadanes2D(vector<vector<ll>>& pf) {
    ll ans = LONG_LONG_MIN;
    for (int i = 1; i < pf.size(); i++) {
        ll best = LONG_LONG_MIN, cur = 0;
        for (int j = i; j < pf.size(); j++) {
            for (int c = 1; c < pf[i].size(); c++) {
                cur += calcArea(i, c, j, c, pf);
                best = max(best, cur);
                cur = max(cur, (ll)0);
            }
        }
        ans = max(ans, best);
    }
    return ans;
}