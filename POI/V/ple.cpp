/*
 * $File: ple.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some things with 2 attributions, 
 *   find the minimal cost that you choose 
 *   some things, and the sum of the first
 *   attribution of the things you choose
 *   is at least A, and B for the second
 *   attribution.
 *
 * Solution:
 *   Dynamic programming. Simple dp.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxT = 21, kMaxA = 79, kInf = 0x3f3f3f3f;
int t, a, n, dp[2][kMaxT + 1][kMaxA + 1], des, src;

int main() {
	scanf("%d%d%d", &t, &a, &n);
	des = 0, src = 1;
	memset(dp[des], 0x3f, sizeof(dp[des]));
	dp[des][0][0] = 0;
	for (int i = 0, t_, a_, w; i < n; ++ i) {
		scanf("%d%d%d", &t_, &a_, &w);
		des ^= 1, src ^= 1;
		memset(dp[des], 0x3f, sizeof(dp[des]));
		for (int j = 0; j <= t; ++ j)
			for (int k = 0; k <= a; ++ k) {
				dp[des][j][k] = min(dp[des][j][k], dp[src][j][k]);
				if (dp[src][j][k] != kInf) {
					int nj = (j + t_ > t ? t : j + t_);
					int nk = (k + a_ > a ? a : k + a_);
					dp[des][nj][nk] = min(dp[des][nj][nk], dp[src][j][k] + w);
				}
			}
	}
	printf("%d\n", dp[des][t][a]);
	return 0;
}
