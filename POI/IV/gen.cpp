/*
 * $File: gen.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some rules like S -> AB that means
 *   a S in a string can be changed to AB,
 *   and some target string, find the minimal
 *   number of S to construct the strings.
 *
 * Solution:
 *   Dynamic programming. Firstly we define
 *   cnt[l][r], which means the set of chars
 *   that can construct the [l, r] of a the
 *   target. Then let DP[i] mean the minimal S
 *   we need to construct the first i letters.
 *   Brute force to implement.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int rule[26][26];
int n, m;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static char buf[4];
		scanf("%s", buf);
		rule[buf[1] - 'A'][buf[2] - 'A'] |= 1 << (buf[0] - 'A');
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++ i) {
		static char buf[128];
		scanf("%s", buf);
		n = strlen(buf);
		static int memo[128], *dp;
		static int cnt[127][127];
		for (int j = 0; j < n; ++ j) cnt[j][j] = 1 << (buf[j] - 'A');
		for (int l = 1; l < n; ++ l)
			for (int j = 0; j < n - l; ++ j) {
				int k = j + l;
				cnt[j][k] = 0;
				for (int p = j; p < k; ++ p) {
					int lmsk = cnt[j][p], rmsk = cnt[p + 1][k];
					while (lmsk) {
						int p = lmsk & -lmsk;
						lmsk ^= p;
						p = __builtin_ctz(p);
						int now = rmsk;
						while (now) {
							int q = now & -now;
							now ^= q;
							q = __builtin_ctz(q);
							cnt[j][k] |= rule[p][q];
						}
					}
				}
			}
		dp = memo + 1;
		memset(memo, 0x3f, sizeof(memo));
		dp[-1] = 0;
		for (int j = 0; j < n; ++ j)
			for (int k = -1; k < j; ++ k)
				if (cnt[k + 1][j] >> ('S' - 'A') & 1) dp[j] = min(dp[j], dp[k] + 1);
		if (dp[n - 1] != 0x3f3f3f3f) printf("%d\n", dp[n - 1]);
		else printf("NIE\n");
	}
	return 0;
}
