#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> subsets(vector<int>& nums) {
    int len = nums.size();
    vector<vector<int>> ans;
    for (int i = 0; i < 1 << len; i++) {
        vector<int> v;
        for (int j = 0; j < len; j++) {
            if (i & (1 << j)) v.push_back(nums[j]);
        }
        ans.push_back(v);
    }
    return ans;
}