#include <bits/stdc++.h>
using namespace std;

template<typename T> class Combinatorics {
    // T = MInt<Modulo>, for obvious reasons.
    private:
        vector<T> fact, invFact;
        int ptr = 0;
    public:
        Combinatorics() {}
        Combinatorics(int n) { reserve(n); }
        void reserve(int size) {
            if (ptr == 0) {
                fact.emplace_back(1);
                invFact.emplace_back(1);
                ptr = 1;
            }
            if (size < ptr) continue;
            fact.resize(size + 1);
            invFact.resize(size + 1);
            for (int i = ptr; i <= size; i++) {
                fact[i] = fact[i - 1] * T(i);
            }
            invFact[size] = T(1) / fact[size];
            for (int i = size - 1; i >= ptr; i--) {
                invFact[i] = invFact[i + 1] * T(i + 1);
            }
            ptr = size + 1;
        }
        T combine(int n, int k) { 
            assert(n >= k), reserve(n);
            return fact[n] * invFact[k] * invFact[n - k]; 
        }
        T permute(int n, int k) { 
            assert(n >= k), reserve(n); 
            return fact[n] * invFact[n - k];
        }
        T getInv(int n) { reserve(n); return invFact[n] * fact[n - 1]; }
        T getInvFact(int n) { reserve(n); return invFact[n]; }
        T getFact(int n) { reserve(n); return fact[n]; }
};