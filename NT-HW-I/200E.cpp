#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 300, kMaxM = 300000, kInf = 0x3f3f3f3f;
int n, m, c3, c4, c5;
int ans[3], val;

int ExGcd(int a, int b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	else {
		int g = ExGcd(b, a % b, x, y);
		ll t = x;
		x = y, y = t - (a / b) * x;
		return g;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, x; i < n; ++ i) {
		scanf("%d", &x);
		if (x == 3) ++ c3;
		if (x == 4) ++ c4;
		if (x == 5) ++ c5;
	}
	val = kInf;
	int M = m;
	for (int w4 = 0; c4 * w4 <= m; ++ w4) {
		int Q = c4 * w4, P = M - Q;
		// c3 * w3 + c5 * w5 = P
		ll x, y;
		int g = ExGcd(c3, c5, x, y);
		if (P % g) continue;
		x *= P / g, y *= P / g;
		if (x < 0) {
			x += ((-x - 1) / (c5 / g) + 1) * (c5 / g);
		}
		else {
			x -= (x / (c5 / g)) * (c5 / g);
		}
		if (x > w4) continue;
		y = (P - c3 * x) / c5;
		if (y < w4) continue;
		int lb = 0, rb = (w4 - x) / (c5 / g) + 1;
		while (lb + 1 < rb) {
			int mid = (lb + rb) >> 1;
			if (y - (c3 / g) * mid >= w4) lb = mid;
			else rb = mid;
		}
		int st = 0, ed = lb;
		lb = min(Q, P - Q), rb = max(Q, P - Q);
		while (ed - st >= 3) {
			int lm = st + (ed - st) / 3, rm = ed - (ed - st) / 3;
			int lv, rv, w3;
			w3 = x + lm * (c5 / g);
			lv = abs(c3 * w3 - lb) + abs(c3 * w3 - rb);
			w3 = x + rm * (c5 / g);
			rv = abs(c3 * w3 - lb) + abs(c3 * w3 - rb);
			if (lv > rv)
				st = lm;
			else
				ed = rm;
		}
		int tmp = kInf, rec;
		for (int i = st; i <= ed; ++ i) {
			int w3 = x + i * (c5 / g);
			int v = abs(c3 * w3 - lb) + abs(c3 * w3 - rb);
			if (v < tmp) {
				tmp = v;
				rec = i;
			}
		}
		if (tmp < val) {
			val = tmp;
			ans[0] = x + rec * (c5 / g);
			ans[1] = w4;
			ans[2] = y - rec * (c3 / g);
		}
	}
	if (val == kInf) printf("-1\n");
	else printf("%d %d %d\n", ans[0], ans[1], ans[2]);
	return 0;
}
