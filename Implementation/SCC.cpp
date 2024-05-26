#include <bits/stdc++.h>
using namespace std;

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