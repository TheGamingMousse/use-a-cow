#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
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
struct SCC {
	int N, ti = 0;
	vector<vector<int>> adj;
	vector<int> disc, comp, st, comps;
	SCC(int _N) : N(_N), adj(N), disc(N), comp(N, -1) {}
	void ae(int x, int y) { adj[x].push_back(y); }
	int dfs(int x) {
		int low = disc[x] = ++ti;
		st.push_back(x);
		for (int y : adj[x])
			if (comp[y] == -1) low = min(low, disc[y] ?: dfs(y));
		if (low == disc[x]) {
			comps.push_back(x);
			for (int y = -1; y != x; ) {
                comp[y = st.back()] = x, st.pop_back();
            }
		}
		return low;
	}
	void gen() {
		for (int i = 0; i < N; i++)
			if (!disc[i]) dfs(i);
		reverse(begin(comps), end(comps));
	}
};