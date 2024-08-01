#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * String hashing... stores the hashes for every prefix.
 * Build: O(n), Query: O(1).
 * Failure Probability: O(|S||H|^2 / M)
 */
class HashedString {
  public:
	static const ll M = (1ll << 61) - 1;
	static const ll B;
	static __int128 mul(ll a, ll b) { return (__int128)a * b; }
	static ll mod_mul(ll a, ll b) { return mul(a, b) % M; }

  private:
	static vector<ll> pow; // pow[i] = P^i % M
	vector<ll> p_hash;     // p_hash[i] = hash of first i characters in string

  public:
    HashedString() {}
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) { pow.push_back(mod_mul(pow.back(), B)); }
		p_hash[0] = 0;
		for (int i = 0; i < (int) s.size(); i++) {
			p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M;
		}
	}

	/** @return length of the string */
	int size() { return (int) p_hash.size() - 1; }

	/** @return hash of the substring [l, r] */
	ll get_hash(int l, int r) {
		ll res = p_hash[r + 1] - mod_mul(p_hash[l], pow[r - l + 1]);
		return (res + M) % M;
	}
};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<ll> HashedString::pow = {1};
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);