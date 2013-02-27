#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long Hash;
const int kMaxN = 100000, kSeed = 99991;
int n, f[kMaxN], g[kMaxN + 1];
char buf[kMaxN + 1];
Hash p[kMaxN], prefix[kMaxN + 1], *pre = prefix + 1, suffix[kMaxN + 1], *suf = suffix;
vector<pair<int, int> > sol, ans;

#define HASH(l, r) (pre[r] - pre[(l) - 1] * p[(r) - (l) + 1])
#define RHASH(l, r) (suf[l] - suf[(r) + 1] * p[(r) - (l) + 1])

bool Cmp(const vector<pair<int, int> > &a, const vector<pair<int, int> > &b) {
	int aa = 0, bb = 0;
	for (int i = 0; i < (int)a.size(); ++ i) aa += a[i].second;
	for (int i = 0; i < (int)b.size(); ++ i) bb += b[i].second;	
	return (aa < bb);
}

void PreWork() {
	int k = 0;
	for (int i = 1; i < n; ++ i) {
		int p = k + f[k];
		if (p >= i && i + f[2 * k - i] < p) f[i] = f[2 * k - i];
		else {
			if (p >= i) f[i] = p - i;
			while (i - f[i] - 1 >= 0 && i + f[i] + 1 < n && buf[i - f[i] - 1] == buf[i + f[i] + 1]) ++ f[i];
			k = i;
		}
	}
	p[0] = 1;
	for (int i = 1; i < n; ++ i) p[i] = p[i - 1] * kSeed;
	pre[-1] = 0;
	for (int i = 0; i < n; ++ i) pre[i] = pre[i - 1] * kSeed + buf[i];
	suf[n] = 0;
	for (int i = n - 1; i >= 0; -- i) suf[i] = suf[i + 1] * kSeed + buf[i];
	memset(g, -1, sizeof(g));
	for (int i = 0; i < n; ++ i)
		if (buf[i] == buf[n - 1]) {
			g[1] = i;
			break;
		}
	for (int i = 1; i < n; ++ i) {
		if (g[i] == -1) break;
		if (buf[n - i - 1] == buf[g[i] + i]) g[i + 1] = g[i];
		else {
			Hash h = RHASH(n - i - 1, n - 1);
			g[i + 1] = g[i] + 1;
			while (g[i + 1] < n && g[i + 1] + i < n && HASH(g[i + 1], g[i + 1] + i) != h) ++ g[i + 1];
			if (g[i + 1] + i >= n) g[i + 1] = -1;
		}
	}
}

int main() {
	scanf("%s", buf);
	n = strlen(buf);
	PreWork();
	for (int i = 0; i < n; ++ i) {
		int l = i - f[i], r = i + f[i];
		sol.clear();
		sol.push_back(make_pair(l, f[i] * 2 + 1));
		if (Cmp(ans, sol)) ans = sol;
		if (r + 1 < n) {
			int lb = 1, rb = n - r;
			while (lb + 1 < rb) {
				int mid = (lb + rb) >> 1;
				if (g[mid] != -1 && g[mid] + mid - 1 < l) lb = mid;
				else rb = mid;
			}
			if (g[lb] != -1 && g[lb] + lb - 1 < l) {
				sol.clear();
				sol.push_back(make_pair(g[lb], lb));
				sol.push_back(make_pair(l, f[i] * 2 + 1));
				sol.push_back(make_pair(n - lb, lb));
				if (Cmp(ans, sol)) ans = sol;
			}
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < int(ans.size()); ++ i) printf("%d %d\n", ans[i].first + 1, ans[i].second);
	return 0;
}
