#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
struct Edge {
    int a, b, w;
    bool operator<(const Edge& y) const {
        return w < y.w;
    }
};
int dr[]{1, 0}, dc[]{0, 1};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    int a, b, n, m; cin >> a >> b >> n >> m;
    vector<int> vert(n), horiz(m);
    for (int& i : vert) cin >> i;
    for (int& i : horiz) cin >> i;
    vert.push_back(b), horiz.push_back(a);
    sort(begin(vert), end(vert));
    sort(begin(horiz), end(horiz));
    int vertPrev = 0, horizPrev = 0; ++n, ++m;
    auto id = [&](int i, int j) {
        if (n >= m) return i * n + j;
        else return i * m + j;
    };
    vector<Edge> lst;
    for (int i = 0; i < n; i++) { // vert
        for (int j = 0; j < m; j++) { // horiz
            int vertPrev = (i > 0) ? vert[i - 1] : 0;
            int horizPrev = (j > 0) ? horiz[j - 1] : 0;
            for (int k = 0; k < 2; k++) {
                int r1 = i + dr[k], c1 = j + dc[k];
                int id1 = id(i, j), id2 = id(r1, c1);
                if (r1 >= 0 && r1 < n &&
                    c1 >= 0 && c1 < m) {
                    Edge res;
                    if (r1 != i) {
                        res = {id1, id2, horiz[j] - horizPrev};
                    } else {
                        res = {id1, id2, vert[i] - vertPrev};
                    }
                    lst.push_back(res);
                }
            }
        }
    }
    sort(begin(lst), end(lst));
    int sz = (n >= m) ? n * (n - 1) + m + 1
         : m * (m - 1) + n + 1;
    DSU dsu(sz);
    ll ans = 0;
    for (auto& i : lst) {
        if (dsu.unite(i.a, i.b)) {
            ans += i.w;
        }
    }
    cout << ans << '\n';
}
/*
Algorithm:
Construct a graph with each node being
a isolated area, and an edge to another
node being the length of fence between them.
Use kruskal's algorithm to get a MST.

Note: This algorithm runs VERY close to the
time limit. It got 1962 ms on the last TC,
and TLE'd on the last TC the first time I ran
it.
*/