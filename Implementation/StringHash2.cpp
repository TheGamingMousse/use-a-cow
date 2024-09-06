#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class HashedString {
  private:
	static const long long M = 1e9 + 9;
	static const long long B;
	static vector<long long> pow;
	vector<long long> p_hash;

  public:
	HashedString() {}
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size()) { 
            pow.push_back((pow.back() * B) % M); 
        }
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

    inline int size() {
        return (int) p_hash.size() - 1;
    }

    /** @return hash of [l, r] */
	long long get_hash(int l, int r) {
		long long raw = p_hash[r + 1] - (p_hash[l] * pow[r - l + 1]);
		return (raw % M + M) % M;
	}
};
vector<ll> HashedString::pow = {1};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);