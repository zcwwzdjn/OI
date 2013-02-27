#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000, kMod = 1000000009;
int n, ans, p[kMaxN];

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

int main() {
	p[0] = 1;
	for (int i = 1; i < kMaxN; ++ i) {
		p[i] = p[i - 1];
		UPT(p[i], p[i - 1]);
	}
	scanf("%d", &n);
	for (int i = 2, mul = 1, tmp = 1; i <= n; ++ i) {
		if (i == 2) {
			UPT(ans, 1);
		}
		else {
			if (i > 4 && (i & 1)) {
				int j = (i - 3) / 2;
				UPT(tmp, (long long)4 * p[j - 1] % kMod);
				mul = (long long)mul * tmp % kMod;
				UPT(ans, mul);
			}
			else {
				UPT(ans, mul);
			}
		}
	}
	UPT(ans, ans);
	ans = (long long)ans * ans % kMod;
	UPT(ans, ans);
	UPT(ans, 2);
	printf("%d\n", ans);
	return 0;
}
