#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * The Z function is basically an array
 * where z[i] = LCP between s[0....n] and s[i...n].
 * z[0] = s.length in this implementation.
 * @return Z function of the string s.
 */
vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    z[0] = n;
    return z;
}