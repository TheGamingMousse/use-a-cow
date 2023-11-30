#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int knapsack(vector<int>& val, vector<int>& wt, int cap) {
    vector<int> dp(cap + 1); 
    for (int i = 0; i < val.size(); i++) {
        for (int j = cap; j >= wt[i]; j--) {
            dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
        }
    }
    return dp[cap];
}
int lcs(string& a, string& b) {
    int n = a.length(), m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                dp[i + 1][j + 1] = 1 + dp[i][j];
            } else {
                dp[i + 1][j + 1]= max(
                    dp[i + 1][j], dp[i][j + 1]
                );
            }
        }
    }
    return dp[n][m];
}
int lis(vector<int>& nums) {
    vector<int> sub;
    for (int i : nums) {
        int idx = lower_bound(begin(sub), end(sub), i) - begin(sub);
        if (idx != sub.size()) {
            sub[idx] = i;
        } else {
            sub.push_back(i);
        }
    }
    return sub.size();
}
int wscheduling(vector<pair<pair<int, int>, int>>& jobs) {
    sort(begin(jobs), end(jobs));
    int n = jobs.size();
    vector<int> dp(n);
    dp[0] = jobs[0].s;
    for (int i = 1; i < n; i++) {
        dp[i] = max(dp[i - 1], jobs[i].s);
        for (int j = i - 1; j >= 0; j--) {
            if (jobs[j].f.f <= jobs[i].f.s) {
                dp[i] = max(dp[i], jobs[i].s + dp[j]);
                break;
            }
        }
    }
    return dp[n - 1];
}