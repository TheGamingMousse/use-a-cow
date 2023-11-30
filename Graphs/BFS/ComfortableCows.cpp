#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

int grid[3000][3000], total = 0;
void solve(int r, int c) {
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    queue<pair<int, int>> q;
    q.push({r, c});
    auto process = [&](int r, int c) {
        if (!grid[r][c]) return;
        int occ = 0;
        for (int i = 0; i < 4; i++) {
            if (grid[r + dr[i]][c + dc[i]]) occ++;
        }
        if (occ == 3) {
            total++;
            for (int i = 0; i < 4; i++) {
                if (!grid[r + dr[i]][c + dc[i]]) {
                    grid[r + dr[i]][c + dc[i]] = 2;
                    q.push({r + dr[i], c + dc[i]});
                }
            }
        }
    };
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        process(p.f, p.s);
        for (int i = 0; i < 4; i++) {
            process(p.f + dr[i], p.s + dc[i]);
        }
    }
    cout << total << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int r, c; cin >> r >> c; 
        r += 1000, c += 1000;
        if (grid[r][c] == 2) {
            grid[r][c] = 1;
            cout << --total << '\n';
        } else {
            grid[r][c] = 1;
            solve(r, c);
        }
    }
}
/*
Algorithm:
We are using a floodfill-like BFS algorithm to add cows.

The logic:
If you add a cow, there are 3 cases:
a. The cow is completely alone (not next to any cows). You don't have to 
worry aboutthis case and can just print out your previous answer.
b. The cow is on a spot we had to add a cow earlier. In this case,
you don't have to worry at all because the grid is still the
same and is still optimal. You'll just need to print out the previous answer - 1.
c. The cow is next to a group of cows. Every cow added will be placed in a queue.
For each cow placed in the queue, the following steps will happen.
1. The current cow will be processed. 
2. The cows next to the current cow will be processed, in case the
current cow or if the cow that might need to be placed affects
the adjacent cows.
The processing consists of checking if there needs to be a cow placed.
If so, that cow will be marked on the grid and pushed to the queue.
*/