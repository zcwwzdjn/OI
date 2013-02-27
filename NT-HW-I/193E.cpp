#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll kN = 10000000000000LL;
const int kMod[2] = {8192, 1953125};
const int kRange[2] = {12288, 7812500};
ll x;
int mod[2];
vector<int> pos[2];

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kN) (x) -= kN; \
}

inline ll Mul(ll a, ll b) {
	if (a < b) swap(a, b);
	ll res = 0;
	while (b) {
		if (b & 1) UPT(res, a);
		b >>= 1;
		UPT(a, a);
	}
	return res;
}

struct Matrix {
	ll v[2][2];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	Matrix() {
		clear();
	}
} e, f, a;

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix c;
	for (int i = 0; i < 2; ++ i)
		for (int k = 0; k < 2; ++ k) if (a.v[i][k])
			for (int j = 0; j < 2; ++ j)
				UPT(c.v[i][j], Mul(a.v[i][k], b.v[k][j]));
	return c;
}

Matrix PowerMod(const Matrix &a, ll b) {
	Matrix res = e, tmp = a;
	while (b) {
		if (b & 1) res = res * tmp;
		b >>= 1;
		tmp = tmp * tmp;
	}
	return res;
}

vector<int> Find(int rest, int mod, int range) {
	vector<int> res;
	int a = 0, b = 1, p = 0;
	while (p < range) {
		if (a == rest) res.push_back(p);
		int c = (a + b) % mod;
		a = b, b = c;
		++ p;
	}
	return res;
}

ll Calc(ll y) {
	a.clear();
	a.v[0][0] = 0;
	a.v[1][0] = 1;
	a = PowerMod(f, y) * a;
	return a.v[0][0];
}

ll ExGcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	else {
		ll g = ExGcd(b, a % b, x, y);
		ll t = x;
		x = y, y = t - a / b * x;
		return g;
	}
}

int main() {
	ll p, q, g;
	g = ExGcd(kRange[0], kRange[1], p, q);
	ll sol[2][2];
	sol[0][0] = p, sol[0][1] = q;
	sol[1][0] = p, sol[1][1] = q;
	while (sol[0][1] - kRange[0] / g >= 0) {
		sol[0][1] -= kRange[0] / g;
		sol[0][0] += kRange[1] / g;
	}
	while (sol[1][0] < 0) {
		sol[1][0] += kRange[1] / g;
		sol[1][1] -= kRange[0] / g;
	}
	scanf("%I64d", &x);
	for (int i = 0; i < 2; ++ i) {
		mod[i] = x % kMod[i];
		pos[i] = Find(mod[i], kMod[i], kRange[i]);
		if (pos[i].size() == 0) {
			puts("-1");
			return 0;
		}
	}
	e.v[0][0] = e.v[1][1] = 1;
	f.v[0][1] = f.v[1][0] = f.v[1][1] = 1;
	ll ans = LONG_LONG_MAX;
	for (int i = 0; i < int(pos[0].size()); ++ i)
		for (int j = 0; j < int(pos[1].size()); ++ j) {
			ll t = pos[0][i] - pos[1][j];
			if (t % g != 0) continue;
			if (t >= 0) {
				p = sol[0][0] * (t / g), q = sol[0][1] * (t / g);
				q -= (q / (kRange[0] / g)) * (kRange[0] / g);
				for (int k = 0; k < 1000; ++ k) {
					ll y = q * kRange[1] + pos[1][j];
					if (y >= ans) break;
					if (Calc(y) == x) {
						ans = min(ans, y);
						break;
					}
					q += kRange[0] / g;
				}
			}
			else {
				t = -t;
				p = sol[1][0] * (t / g), q = sol[1][1] * (t / g);
				p -= (p / (kRange[1] / g)) * (kRange[1] / g);
				for (int k = 0; k < 1000; ++ k) {
					ll y = p * kRange[0] + pos[0][i];
					if (y >= ans) break;
					if (Calc(y) == x) {
						ans = min(ans, y);
						break;
					}
					p += kRange[1] / g;
				}
			}
		}
	printf("%I64d\n", ans);
	return 0;
}
