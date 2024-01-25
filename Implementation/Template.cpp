#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

// const int MOD = 1e9 + 7;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {

}
/**
 * TASK:
 * 
*/
/* Stuff to look for:
	* Overflow, OOB.
	* Corner Cases.
	* Do something, stay organized!
	* WRITE STUFF!
	* THINK OF MULTIPLE APPROACHES
*/
/**
 * Mod Arithmetic Stuff:
 * template<class T> void add(T& a, T b) {
 *   a += b, a %= MOD;
 * }
 * template<class T> void sub(T& a, T b) {
 *   a > b ? a -= b : a -= B, a += MOD;
 * }
 * template<class T> void mul(T& a, T b) {
 *     a = (a * b) % MOD;
 * }
*/