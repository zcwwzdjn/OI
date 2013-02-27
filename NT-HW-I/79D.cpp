#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kMaxK = 10, kMaxM = kMaxK * 2, kMaxL = 100;
int n, k, l, s[kMaxN + 2], t[kMaxN + 1], p[kMaxL];
int m, pos[kMaxM];
int dis[kMaxM][kMaxN + 1];

int Solve(int mask) {
	static int memo[1 << kMaxM];
	static bool done[1 << kMaxM];
	if (done[mask]) return memo[mask];
	int &res = memo[mask];
	done[mask] = true;
	if (mask == 0) return (res = 0);
	else if (__builtin_popcount(mask) == 1) return (res = -1);
	int seq[kMaxM], idx = 0;
	int now = mask;
	while (now) {
		int p = now & -now;
		now ^= p;
		seq[idx ++] = __builtin_ctz(p);
	}
	res = 0x3f3f3f3f;
	for (int i = 0; i < idx - 1; ++ i)
		for (int j = i + 1; j < idx; ++ j) {
			int tmp = Solve(mask ^ (1 << seq[i]) ^ (1 << seq[j]));
			if (tmp != -1) res = min(res, tmp + dis[seq[i]][pos[seq[j]]]);
		}
	if (res == 0x3f3f3f3f) res = -1;
	return res;
}

int main() {
	scanf("%d%d%d", &n, &k, &l);
	for (int i = 0, x; i < k; ++ i) {
		scanf("%d", &x);
		s[x] = 1;
	}
	for (int i = 0; i < l; ++ i) scanf("%d", &p[i]);
	for (int i = 0; i <= n; ++ i) {
		t[i] = s[i] ^ s[i + 1];
		if (t[i] == 1) pos[m ++] = i;
	}
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 0; i < m; ++ i) {
		dis[i][pos[i]] = 0;
		static int q[kMaxN + 1];
		int qh = 0, qt = 0;
		q[qt ++] = pos[i];
		while (qh < qt) {
			int u = q[qh ++];
			for (int j = 0; j < l; ++ j) {
				int v = u + p[j];
				if (v <= n && dis[i][v] > dis[i][u] + 1) {
					dis[i][v] = dis[i][u] + 1;
					q[qt ++] = v;
				}
				v = u - p[j];
				if (v >= 0 && dis[i][v] > dis[i][u] + 1) {
					dis[i][v] = dis[i][u] + 1;
					q[qt ++] = v;
				}
			}
		}
	}
	printf("%d\n", Solve((1 << m) - 1));
	return 0;
}
