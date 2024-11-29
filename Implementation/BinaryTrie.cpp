#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int BITS = 30;

struct Trie {
    int timer = 0;
    vector<int> freq;
    vector<array<int, 2>> adj;
    Trie(int vals) : adj(32 * vals), freq(32 * vals) {}

    /** inserts x into the trie */
    void insert(int x) {
        int cur = 0;
        for (int i = BITS; i >= 0; i--) {
            int v = (x >> i) & 1;
            if (!adj[cur][v]) {
                adj[cur][v] = ++timer;
            }
            cur = adj[cur][v];
            freq[cur]++;
        }
    }

    void remove(int x) {
        int cur = 0;
        for (int i = BITS; i >= 0; i--) {
            int v = (x >> i) & 1;
            cur = adj[cur][v];
            freq[cur]--;
        }
    }

    /** @return the maximum xor pair possible */
    int walk(int x) {
        int node = 0, cur = 0;
        for (int i = BITS; i >= 0; i--) {
            int v = (x >> i) & 1;
            if (adj[node][!v] && freq[adj[node][!v]]) {
                node = adj[node][!v];
                cur |= 1 << i;
            } else {
                node = adj[node][v];
            }
        }
        return cur;
    }
};