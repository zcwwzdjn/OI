/*
 * $File: tan.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some hotels on a axis, you
 *   start from 0 and end with D. You
 *   may need to relax at some hotels,
 *   and you can't walk more than 800
 *   in a trip from a hotel to another.
 *   Find the minimal cost and the minimal
 *   number of hotels you must choose.
 *
 * Solution:
 *   Dynamic programming. I do it in O(N^2),
 *   but it can be done in O(n) with some
 *   tricks.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int d, n, p[kMaxN + 1], w[kMaxN + 1][2];
int dp[kMaxN + 1][2], pre[kMaxN + 1];
int seq[kMaxN + 1];

void SolveWhenConsiderW(int t) {
	memset(dp, 0x3f, sizeof(dp));
	dp[0][t] = w[0][t];
	dp[0][t ^ 1] = w[0][t ^ 1];
	for (int i = 1; i <= n; ++ i)
		for (int j = 0; j < i; ++ j)
			if (p[i] - p[j] <= 800) {
				if (dp[j][t] + w[i][t] < dp[i][t]) {
					dp[i][t] = dp[j][t] + w[i][t];
					dp[i][t ^ 1] = dp[j][t ^ 1] + w[i][t ^ 1];
					pre[i] = j;
				}
				else if (dp[j][t] + w[i][t] == dp[i][t] && dp[j][t ^ 1] + w[i][t ^ 1] < dp[i][t ^ 1]) {
					dp[i][t ^ 1] = dp[j][t ^ 1] + w[i][t ^ 1];
					pre[i] = j;
				}
			}
	int r = -1;
	for (int i = 0; i <= n; ++ i)
		if (d - p[i] <= 800) {
			if (r == -1) r = i;
			else if (dp[i][t] < dp[r][t]) r = i;
			else if (dp[i][t] == dp[r][t] && dp[i][t ^ 1] < dp[r][t ^ 1]) r = i;
		}
	seq[0] = 0;
	while (r) {
		seq[++ seq[0]] = p[r];
		r = pre[r];
	}
	for (int i = seq[0]; i >= 1; -- i) {
		printf("%d", seq[i]);
		if (i > 1) putchar(' ');
	}
	puts("");
}

int main() {
	scanf("%d%d", &d, &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", &p[i], &w[i][0]);
		w[i][1] = 1;
	}
	for (int i = 0; i < 2; ++ i)
		SolveWhenConsiderW(i);
	return 0;
}
