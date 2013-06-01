#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, a, b;
char buf[222];
int dp[222][222][222];

inline void upt(int &des, int src) {
	des = min(des, src);
}

int main() {
	scanf("%d%d%d%s", &n, &a, &b, buf + 1);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0] = 0;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j <= a; ++ j)
			for (int k = 0; k <= b; ++ k) {
				upt(dp[i + 1][j][k], dp[i][j][k] + (buf[i + 1] != '2'));
				upt(dp[i + 1][j + 1][k], dp[i][j][k] + (buf[i + 1] != '0'));
				upt(dp[i + 1][j][k + 1], dp[i][j][k] + (buf[i + 1] != '1'));
			}
	if (a + b > n) puts("-1");
	else {
		printf("%d\n", dp[n][a][b]);
		for (int i = n; i >= 1; -- i) {
			if (dp[i][a][b] == dp[i - 1][a][b] + (buf[i] != '2')) {
				buf[i] = '2';
			}
			else if (a && dp[i][a][b] == dp[i - 1][a - 1][b] + (buf[i] != '0')) {
				buf[i] = '0';
				-- a;
			}
			else {
				buf[i] = '1';
				-- b;
			}
		}
		puts(buf + 1);
	}
	return 0;
}
