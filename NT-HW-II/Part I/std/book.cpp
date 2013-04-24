#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

#ifdef unix
#define FMT "%lld"
#else
#define FMT "%I64d"
#endif

typedef long long ll;
const int kMaxN = 100000;
int n, x, a, b;
ll m, d[kMaxN - 1];

int main() {
	scanf("%d%d%d%d" FMT, &n, &x, &a, &b, &m);
	m -= (ll)n * x;
	ll p = (ll)n * a * (n - 1), q = m + (ll)(n - 1) * n / 2 * a;
	ll c = (p - q) / (a + b);
	set<ll> s;
	for (int i = 1; i < n; ++ i) s.insert(i);
	for (int i = 0; i < n - 1; ++ i) d[i] = a;
	while (c) {
		set<ll>::iterator it = s.lower_bound(c + 1);
		if (it == s.begin()) break;
		-- it;
		c -= *it;
		d[n - (*it) - 1] = -b;
		s.erase(it);
	}
	ll e = x;
	for (int i = 0; i < n; ++ i) {
		if (i) printf(" ");
		printf(FMT, e);
		if (i + 1 < n) e += d[i];
	}
	printf("\n");
	return 0;
}
