#include <bits/stdc++.h>
using namespace std;

/**
 * Solves the equation ax + by = gcd(a, b).
 * Returns {gcd(a, b), x, y}.
 * 
 * Stolen from Brian again.
 */
template<typename T> array<T, 3> extendedGCD(T m, T n) {
    T a = 1, a_in = 0, b = 0, b_in = 1;
    while (n) {
        const T q = m / n;
        a_in = exchange(a, a_in) - q * a_in;
        b_in = exchange(b, b_in) - q * b_in;
        n = exchange(m, n) - q * n;
    }
    return array<T, 3>({m, a, b});
}