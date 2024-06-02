#include <bits/stdc++.h>
using namespace std;

template<typename T> struct RMQ {
	vector<T> v; int n;
	constexpr int b = 30;
	vector<int> mask, t;
	int op(int x, int y) { return v[x] < v[y] ? x : y; }
	int lsb(int x) { return x & -x; }
	int msb(int x) { return __lg(x); }
	int small(int r, int size = b) {
		return r - msb(mask[r] & ((1 << size) - 1));
	}
	void init(vector<T>& _v) {
        v = _v, n = (int) v.size();
        mask = t = vector<int>(n);
		int cur = 0;
		for (int i = 0; i < n; i++) {
			cur = (cur << 1) & ((1 << b) - 1);
			while (cur > 0 && op(i, i - msb(lsb(cur))) == i) {
				cur ^= lsb(cur);
			}
			mask[i] = cur |= 1;
		}
		for (int i = 0; i < n / b; i++) { 
            t[i] = small(b * i + b - 1); 
        }
		for (int j = 1; (1 << j) <= n / b; j++) {
            for (int i = 0; i + (1 << j) <= n / b; i++) {
                int idx = (n / b) * (j - 1) + i;
			    t[idx + (n / b)] = op(t[idx], t[idx + (1 << (j - 1))]);
            }
        }
	}
	T query(int l, int r) {
		if (r - l + 1 <= b) return v[small(r, r - l + 1)];
		int ans = op(small(l + b - 1), small(r));
		int x = l / b + 1, y = r / b - 1;
		if (x <= y) {
			int j = msb(y - x + 1), idx = (n / b) * j;
			ans = op(ans, op(t[idx + x], t[idx + y - (1 << j) + 1]));
		}
		return v[ans];
	}
};