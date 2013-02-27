#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;
int k, p;
ll l, r;

int PowerMod(int a, ll b, int c) {
	int res = 1, tmp = a % c;
	while (b) {
		if (b & 1) res = (ll)res * tmp % c;
		b >>= 1;
		tmp = (ll)tmp * tmp % c;
	}
	return res;
}

int Solve() {
	cin >> k >> l >> r >> p;
	if (k & 1) {
		if (p == 2) return 0;
		if (k == 1) return 2;
		int b0 = PowerMod(k, PowerMod(2, l, p - 1), p);
		if (k % p == 0 && l) b0 = 0;
		int bn = PowerMod(k, PowerMod(2, r + 1, p - 1), p);
		if (k % p == 0) bn = 0;
		if (b0 == 1) return (2 % p);
		b0 = (b0 - 1 + p) % p;
		bn = (bn - 1 + p) % p;
		return ((ll)bn * PowerMod(b0, p - 2, p) % p * PowerMod(PowerMod(2, r - l, p), p - 2, p) % p); 
	}
	else {
		if (p == 2) return 1;
		int b0 = PowerMod(k, PowerMod(2, l, p - 1), p);
		if (k % p == 0 && l) b0 = 0;
		int bn = PowerMod(k, PowerMod(2, r + 1, p - 1), p);
		if (k % p == 0) bn = 0;
		if (b0 == 1) return PowerMod(2, r - l + 1, p);
		b0 = (b0 - 1 + p) % p;
		bn = (bn - 1 + p) % p;
		return ((ll)bn * PowerMod(b0, p - 2, p) % p);
	}
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --)
		cout << Solve() << endl;
	return 0;
}
