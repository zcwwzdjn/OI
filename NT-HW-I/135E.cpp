#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxK = 1000000, kMod = 1000000007;
int k, w, ans;
int inv[kMaxK + 1], fac[kMaxK + 1], fac_inv[kMaxK + 1];

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

int PowerMod(int a, int b) {
	int res = 1, tmp = a;
	while (b) {
		if (b & 1) res = (ll)res * tmp % kMod;
		b >>= 1;
		tmp = (ll)tmp * tmp % kMod;
	}
	return res;
}

int main() {
	scanf("%d%d", &k, &w);
	fac[0] = fac_inv[0] = 1;
	for (int i = 1; i <= k; ++ i) {
		inv[i] = PowerMod(i, kMod - 2);
		fac[i] = (ll)fac[i - 1] * i % kMod;
		fac_inv[i] = (ll)fac_inv[i - 1] * inv[i] % kMod;
	}
	for (int t = 1; t <= k; ++ t) {
		if (t <= w - 1) {
			UPT(ans, (ll)t * fac[k] % kMod * fac[k] % kMod * PowerMod(k, w - 1 - t) % kMod * fac_inv[k - t] % kMod * fac_inv[k - t] % kMod);
		}
		else {
			UPT(ans, (ll)fac[k] * w % kMod * fac[k - t + w - 1] % kMod * fac_inv[k - t] % kMod * fac_inv[k - t] % kMod);
		}
	}
	for (int t = 1; t < k; ++ t) {
		if (t + 1 <= w - 1) {
			UPT(ans, (ll)t * fac[k] % kMod * fac[k] % kMod * PowerMod(k, w - t - 2) % kMod * fac_inv[k - t] % kMod * fac_inv[k - t - 1] % kMod);
		}
		else {
			UPT(ans, (ll)fac[k] * (w - 1) % kMod * fac[k - t + w - 2] % kMod * fac_inv[k - t] % kMod * fac_inv[k - t - 1] % kMod);
		}
	}
	printf("%d\n", ans);
	return 0;
}
