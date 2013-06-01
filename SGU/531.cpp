#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 200000;
int n, d, x[kMaxN + 1], w[kMaxN + 1], max_w[kMaxN + 1], rec[kMaxN + 1];

int main() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", &x[i], &w[i]);
		if (w[i] < max_w[i - 1]) {
			max_w[i] = max_w[i - 1];
			rec[i] = rec[i - 1];
		}
		else {
			max_w[i] = w[i];
			rec[i] = i;
		}
	}
	int res = 0, a = -1, b = -1;
	for (int i = 2; i <= n; ++ i) {
		if (x[i] - x[1] < d) continue;
		int j = upper_bound(x + 1, x + i, x[i] - d) - x - 1;
		int tmp = w[i] + max_w[j];
		if (tmp > res) {
			res = tmp;
			a = i, b = rec[j];
		}
	}
	printf("%d %d\n", a, b);
	return 0;
}
