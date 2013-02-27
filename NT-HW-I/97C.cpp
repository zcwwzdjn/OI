#include <cstdio>
#include <algorithm>

const int kMaxN = 100;
int n;
double p[kMaxN + 1], ans;

int main() {
	scanf("%d", &n);
	for (int i = 0; i <= n; ++ i) scanf("%lf", &p[i]);
	for (int i = 0; i <= n; ++ i)
		if (n - 2 * i == 0) ans = std::max(ans, p[i]);
		else if (n - 2 * i > 0)
			for (int j = i + 1; j <= n; ++ j)
				if (n - 2 * j < 0) ans = std::max(ans, (p[i] + p[j] * (n - 2 * i) / (2 * j - n)) / (1.0 + (n - 2 * i) * 1.0 / (2 * j - n)));
	printf("%.8lf\n", ans);
	return 0;
}
