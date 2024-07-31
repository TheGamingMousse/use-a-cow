#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * O(sqrt(x)) prime factorization.
 * Well, map accesses might slow it down,
 * but realistically it doesn't matter.
 */
map<int, int> factorize(int x) {
    map<int, int> res;
    for (int i = 2; i * i <= x; i++) {
        if (x % i != 0) { continue; }
        int cnt = 0;
        while (x % i == 0) {
            ++cnt, x /= i;
        }
        res[i] = cnt;
    }
    if (x > 1) { ++res[x]; }
    return res;
}