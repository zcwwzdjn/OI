#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 150, kMod = 51123987;
int n, f[kMaxN + 1][52][52][52];
char buf[kMaxN + 2];
int suc[kMaxN + 1][3];

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

int main() {
	scanf("%d%s", &n, buf + 1);
	for (int i = 1; i <= n; ++ i)
		for (int j = 0; j < 3; ++ j)
			for (int k = i; k <= n; ++ k)
				if (buf[k] - 'a' == j) {
					suc[i][j] = k;
					break;
				}
	int m = (n - 1) / 3 + 1;
	f[0][0][0][0] = 1;
	for (int i = 0; i < n; ++ i) {
		int c[3], e[3];
		for (c[0] = 0; c[0] <= m; ++ c[0])
			for (c[1] = 0; c[1] <= m; ++ c[1])
				for (c[2] = 0; c[2] <= m; ++ c[2])
					if (f[i][c[0]][c[1]][c[2]]) {
						for (int j = 0; j < 3; ++ j) {
							if (c[j] == m) continue;
							memcpy(e, c, sizeof(c));
							++ e[j];
							if (suc[i + 1][j]) UPT(f[suc[i + 1][j] - 1][e[0]][e[1]][e[2]], f[i][c[0]][c[1]][c[2]]);
						}
					}
	}
	int res = 0;
	for (int i = 0; i <= n; ++ i)
		for (int a = 0; a <= m; ++ a)
			for (int b = 0; b <= m; ++ b) {
				int c = n - a - b;
				if (c >= 0 && abs(a - b) <= 1 && abs(a - c) <= 1 && abs(b - c) <= 1) UPT(res, f[i][a][b][c]);
			}
	printf("%d\n", res);
	return 0;
}
