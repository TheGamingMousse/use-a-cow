#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * Generic segtree template written by Brian.
 * forLevels is for segtree walking, forRange for 
 * updates and queries, forParents for pushing down
 * or pulling updates, etc.
 * 
 * (Most of the time I just use recursive tho lmao)
 */
namespace SegmentTree {
    template <typename F>
    int forLevels(int node, int sz, bool dir, F f) {
        while (node < sz) {
            node = node << 1 | dir + (!dir ? f(node) : -f(node));
        }
        return node;
    }

    template <typename F> 
    void forRange(int node_1, int node_2, F f) {
        for (; node_1 < node_2; node_1 >>= 1, node_2 >>= 1) {
            if (node_1 & 1) f(node_1++);
            if (node_2 & 1) f(--node_2);
        }
    } 

    template<typename F> 
    void forParents(int p, bool dir, F f) {
        const int lvls = __lg(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    
    template<typename F> 
    void forRangeOrdered(int node_1, int node_2, bool dir, F f) {
        int base = !dir ? node_1 - 1 : node_2;
        const int mask = (1 << __lg((node_1 - 1) ^ node_2)) - 1;
        const int offset = !dir ? 1 : -1;
        int node = (!dir ? -node_1 : node_2) & mask;
        while (node) {
            const int bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }
        base = dir ? node_1 - 1 : node_2;
        node = (dir ? -node_1 : node_2) & mask;
        while (node) {
            const int bit = __lg(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }
    }
}
