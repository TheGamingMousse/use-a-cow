#include <bits/stdc++.h>
using namespace std;

template<class T> int lis(vector<T> &a) {
    vector<int> dp;
	for (T i : a) {
		int pos = lower_bound(begin(dp), end(dp), i) - dp.begin();
        if (pos == dp.size()) { dp.push_back(i); } 
        else { dp[pos] = i; }
	}
	return dp.size();
}