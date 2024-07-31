#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * String hashing... stores the hashes for every prefix.
 * Build: O(n), Query: O(1).
 * Failure Probability: O(|S||H|^2 / M)
 */
class HashedString {
  private:
	static const ll M = 1e9 + 9;
	static const ll B;
    
	static vector<ll> pow;   // pow[i] = B^i % M
	vector<ll> p_hash;       // p_hash[i] = hash of first i chars

  public:
	HashedString(const string &s) : p_hash(1 + (int) s.size()) {
		while (pow.size() <= s.size()) { 
            pow.push_back((pow.back() * B) % M); 
        }
		p_hash[0] = 0;
		for (int i = 0; i < (int) s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}
    /** @return hash of substring [start, end] */
	ll get_hash(int start, int end) {
		ll raw_val =
		    (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
}; 
vector<ll> HashedString::pow = {1};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);