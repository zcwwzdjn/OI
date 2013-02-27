#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 2000000, kMaxM = kMaxN * 2 + 1, kMod = 51123987;
char ori[kMaxN + 1], buf[kMaxM + 1];
int n, m, f[kMaxM];
int left[kMaxN + 1], right[kMaxN + 1];
int *ll = left, *rr = right;
int ans;

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

void PreWork() {
	int k = 0;
	for (int i = 1; i < m; ++ i) {
		int p = k + f[k];
		if (p > i && i + f[2 * k - i] < p) f[i] = f[2 * k - i];
		else {
			if (p > i) f[i] = p - i; else f[i] = 0;
			while (i - f[i] - 1 >= 0 && i + f[i] + 1 < m && buf[i - f[i] - 1] == buf[i + f[i] + 1]) ++ f[i];
			k = i;
		}
	}
}

int main() {
	scanf("%d%s", &n, ori);
	buf[m ++] = '$';
	for (int i = 0; i < n; ++ i) {
		buf[m ++] = ori[i];
		buf[m ++] = '$';
	}
	PreWork();
	long long sum = 0;
	for (int i = 1; i < m; i += 2) sum += (f[i] + 1) / 2;
	for (int i = 0; i < m; i += 2) sum += f[i] / 2;
	long long tmp = sum - 1;
	if (sum & 1) tmp /= 2; else sum /= 2;
	ans = sum % kMod * (tmp % kMod) % kMod;
	for (int i = 1; i < m; i += 2) {
		++ ll[(i - f[i]) / 2];
		-- ll[(i + 1) / 2];
		++ rr[i / 2];
		-- rr[(i + f[i]) / 2];
	}
	for (int i = 0; i < m; i += 2) {
		++ ll[(i - f[i]) / 2];
		-- ll[(i + 1) / 2];
		++ rr[i / 2];
		-- rr[(i + f[i]) / 2];
	}
	for (int i = 1; i <= n; ++ i) UPT(ll[i], ll[i - 1]);
	for (int i = 1; i <= n; ++ i) UPT(rr[i], rr[i - 1]);
	for (int i = 1, s = rr[0]; i < n; ++ i) {
		ans -= (long long)ll[i] * s % kMod;
		if (ans < 0) ans += kMod;
		UPT(s, rr[i]);
	}
	printf("%d\n", ans);
	return 0;
}
