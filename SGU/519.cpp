#include <cstdio>
#include <algorithm>

using std::max;

const int kMaxN = 100, kMaxM = 100;
int n, m, h[kMaxN][kMaxM];

int main() {
	scanf("%d%d", &n, &m);
	int res = 0;
	for (int i = 0; i < n; ++ i) {
		static char buf[128];
		scanf("%s", buf);
		for (int j = 0; j < m; ++ j) {
			h[i][j] = buf[j] - '0';
			if (h[i][j])
				res += 2;
		}
	}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			int surface = 0;
			if (j == 0 || h[i][j] > h[i][j - 1])
				surface += (j == 0 ? h[i][j] : (h[i][j] - h[i][j - 1]));
			if (j == m - 1 || h[i][j] > h[i][j + 1])
				surface += (j == m - 1 ? h[i][j] : (h[i][j] - h[i][j + 1]));
			res += surface;
		}
	for (int j = 0; j < m; ++ j)
		for (int i = 0; i < n; ++ i) {
			int surface = 0;
			if (i == 0 || h[i][j] > h[i - 1][j])
				surface += (i == 0 ? h[i][j] : (h[i][j] - h[i - 1][j]));
			if (i == n - 1 || h[i][j] > h[i + 1][j])
				surface += (i == n - 1 ? h[i][j] : (h[i][j] - h[i + 1][j]));
			res += surface;
		}
	printf("%d\n", res);
	return 0;
}
