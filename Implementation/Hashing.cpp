#include <bits/stdc++.h>
using namespace std;

struct chash {
	const uint64_t C = uint64_t(2e18 * 3.1415927) + 71;
	const uint32_t R = chrono::steady_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ R) * C);
	}
};
class HashedString {
  private:
	static const long long M = 1e9 + 9;
	static const long long B = 9973;

	static vector<long long> pow;   // pow[i] = B^i % M
	vector<long long> p_hash;       // p_hash[i] = hash of first i chars

  public:
	HashedString(const string &s) : p_hash(1 + (int) s.size()) {
        if (pow.size() <= s.size()) { 
            pow.reserve(1 + s.size()) 
        }
		while (pow.size() <= s.size()) { 
            pow.push_back((pow.back() * B) % M); 
        }
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	long long get_hash(int start, int end) {
		long long raw_val =
		    (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
}; 
// vector<long long> HashedString::pow = {1};