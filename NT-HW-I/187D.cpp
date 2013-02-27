#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kInf = 0x3f3f3f3f;
const int kMaxN = 100000;
int n, m, g, r, t[kMaxN + 2], msum[kMaxN + 2];
ll sum[kMaxN + 2];
int q, cnt;
ll val[kMaxN + 2];
int axis[kMaxN + 1];
int pos[kMaxN + 1];

#define LB(x) ((x) & (-(x)))
namespace idt {
	int node[kMaxN + 1], ori[kMaxN + 1];

	void Init() {
		memset(node, 0x3f, sizeof(node));
		memset(ori, 0x3f, sizeof(ori));
	}

	void Change(int i, int d) {
		ori[i] = d;
		for ( ; i <= cnt; i += LB(i)) node[i] = d;
	}

	int Query(int l, int r) {
		int res = kInf;
		while (r > l) {
			if (r - LB(r) >= l) {
				res = min(res, node[r]);
				r -= LB(r);
			}
			else {
				res = min(res, ori[r]);
				-- r;
			}
		}
		return res;
	}
}
#undef LB

int main() {
	scanf("%d%d%d", &n, &g, &r);
	m = g + r;
	for (int i = 1; i <= n + 1; ++ i) scanf("%d", &t[i]);
	sum[0] = 0;
	for (int i = 1; i <= n + 1; ++ i) {
		sum[i] = sum[i - 1] + t[i];
		msum[i] = ((ll)msum[i - 1] + t[i]) % m;
	}
	for (int i = 1; i <= n; ++ i) axis[cnt ++] = msum[i];
	sort(axis, axis + cnt);
	cnt = unique(axis, axis + cnt) - axis;
	for (int i = 1; i <= n; ++ i) pos[i] = lower_bound(axis, axis + cnt, msum[i]) - axis + 1;
	idt::Init();
	for (int i = n; i >= 0; -- i) {
		int t = kInf, lb, rb;
		if (msum[i] < m - g) {
			int lb = lower_bound(axis, axis + cnt, msum[i] + g) - axis + 1;
			int rb = lower_bound(axis, axis + cnt, m) - axis;
			t = min(t, idt::Query(lb - 1, rb));
		}
		lb = lower_bound(axis, axis + cnt, msum[i] - m + g) - axis + 1;
		rb = lower_bound(axis, axis + cnt, msum[i]) - axis;
		t = min(t, idt::Query(lb - 1, rb));
		if (t > n) val[i] = sum[n + 1] - sum[i];
		else val[i] = sum[t] - sum[i] + m - (sum[t] - sum[i]) % m + val[t];
		if (i > 0) idt::Change(pos[i], i);
	}
	scanf("%d", &q);
	for (int x; q --; ) {
		scanf("%d", &x);
		int y = x % m;
		if (y <= g) {
			int lb = lower_bound(axis, axis + cnt, g - y) - axis + 1;
			int rb = lower_bound(axis, axis + cnt, m - y) - axis;
			int t = idt::Query(lb - 1, rb);
			if (t > n)
				printf("%I64d\n", x + sum[n + 1]);
			else 
				printf("%I64d\n", x + sum[t] + m - (sum[t] + x) % m + val[t]);
		}
		else {
			int lb = lower_bound(axis, axis + cnt, 0) - axis + 1;
			int rb = lower_bound(axis, axis + cnt, m - y) - axis;
			int t = idt::Query(lb - 1, rb);
			lb = lower_bound(axis, axis + cnt, g - y + m) - axis + 1;
			rb = lower_bound(axis, axis + cnt, m) - axis;
			t = min(t, idt::Query(lb - 1, rb));
			if (t > n) 
				printf("%I64d\n", x + sum[n + 1]);
			else 
				printf("%I64d\n", x + sum[t] + m - (sum[t] + x) % m + val[t]);
		}
	}
	return 0;
}
