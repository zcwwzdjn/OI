#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <functional>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 103680, kMaxK = 15;
int k, n, a, b, x, bb;
pair<ll, int> p[kMaxK];
ll f[kMaxK][64], v, ans;
map<ll, pair<int, int> > memo;

void Find(int step, ll cur) {
	if (cur > x) return;
	if (step == k) {
		if (cur > bb) bb = cur;
	}
	else {
		for (int i = p[step].second; i >= 0; -- i)
			Find(step + 1, cur * f[step][i]);
	}
}

void Dfs(int step, ll cur) {
	if (cur > v / cur || cur * cur > v / cur) return;
	if (step == k) {
		if (cur == 1) {
			int t;
			t = 0;
		}
		int aa = cur;
		ll orz = v / aa;
		x = (int)(floor(sqrt(orz)) + 1E-6);
		if ((ll)aa * (x + x) + orz < ans) {
			bb = 1;
			Find(0, 1LL);
			ll cc = v / aa / bb;
			ll tmp = cc * (aa + bb) + (ll)aa * bb;
			if (tmp < ans) {
				ans = tmp;
				a = aa, b = bb;
			}
		}
	}
	else {
		for (int i = p[step].second; i >= 0; -- i) {
			p[step].second -= i;
			Dfs(step + 1, cur * f[step][i]);
			p[step].second += i;
		}
	}
}

void Solve() {
	scanf("%d", &k);
	v = 1LL;
	for (int i = 0; i < k; ++ i) {
		scanf("%I64d%d", &p[i].first, &p[i].second);
		for (int j = 1; j <= p[i].second; ++ j) v *= p[i].first;
	}
	if (memo.count(v)) {
		pair<int, int> r = memo[v];
		int a = r.first, b = r.second;
		ll c = v / a / b;
		ll ans = c * (a + b) + (ll)a * b;
		printf("%I64d %d %d %I64d\n", ans << 1, a, b, c);
		return;
	}
	sort(p, p + k, greater<pair<ll, int> >());
	for (int i = 0; i < k; ++ i) {
		f[i][0] = 1;
		for (int j = 1; j <= p[i].second; ++ j) f[i][j] = f[i][j - 1] * p[i].first;
	}
	ans = LONG_LONG_MAX;
	Dfs(0, 1LL);
	printf("%I64d %d %d %I64d\n", ans << 1, a, b, v / a / b);
	memo[v] = make_pair(a, b);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t --) Solve();
	return 0;
}
