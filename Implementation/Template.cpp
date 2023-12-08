#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

pii operator+(pii p1, pii p2) {
    return make_pair(p1.f + p2.f, p1.s + p2.s);
}
pii operator-(pii p1, pii p2) {
    return make_pair(p1.f - p2.f, p1.s - p2.s);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    // freopen("", "r", stdin);
    // freopen("", "w", stdout);
    auto test = [&]() {
        // test code
    };
    // test()
}
/*
Problem Checklist:
1. What are some possible time
complexities?
2. (Make some observations)
3. Are there any subproblems
that break said problem into
smaller, more workable pieces?
4. (Run through possible ideas:
graph, bisearch, sortings?)
5. If it's a game theory/problem
where there's "choices", are there
any "invariants"?
*/