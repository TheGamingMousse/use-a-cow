#include <bits/stdc++.h>

using ll = long long;

/**
 * Concise fraction template. Requires C++ 20. 
 */
template<class T> struct Fraction {
    T top = 0, bot = 1;

    auto operator<=>(const Fraction &o) const {
        return (top * o.bot) <=> (o.top * bot);
    }

    bool operator==(const Fraction &o) const {
        return (top * o.bot) == (o.top * bot);
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction &f) {
        return os << f.top << '/' << f.bot;
    }
};