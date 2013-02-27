#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int n, m, k, p;
int c[kMaxN + 1][kMaxN + 1];
int cnt[kMaxN + 1], mul[kMaxN + 1];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	if ((n & 1) != (m & 1)) {
		puts("0");
		return 0;
	}
	bool rev = (n < m);
	if (rev) swap(n, m);
	for (int i = 1; i <= n; ++ i) mul[i] = 1;
	for (int x, y, z, i = 0; i < k; ++ i) {
		scanf("%d%d%d", &x, &y, &z);
		if (rev) swap(x, y);
		++ cnt[x];
		mul[x] *= z;
	}
	scanf("%d", &p);
	c[0][0] = 1;
	for (int i = 1; i <= m; ++ i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++ j)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
	}
	int res = 1;
	for (int i = 1, exi = 0; i <= n; ++ i)
		if (cnt[i] || exi) {
			int st = 0, tmp = 0;
			if (mul[i] == 1) ++ st;
			for (int j = st; j <= m - cnt[i]; j += 2)
				tmp = (tmp + c[m - cnt[i]][j]) % p;
			res = (long long)res * tmp % p;
		}
		else exi = 1;
	printf("%d\n", res);
	return 0;
}
