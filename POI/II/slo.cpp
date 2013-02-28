/*
 * $File: slo.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a list of word, try to find a
 *   subsequence of the list, and the
 *   concatenation equals a given pattern.
 *   Count the solutions.
 *
 * Solution:
 *   Dynamic Programming. Let DP[N][L] be the
 *   number of solutions when using the first N
 *   words to construct the first L letters.
 *   Use hashing to speed up the program.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long Hash;
const int kSeed = 99991;
const int kInf = 1000000;
const int kMaxL = 150, kMaxN = 200;
char pat[kMaxL + 2], buf[kMaxN + 1][kMaxL + 2];
int n, dp[kMaxN + 1][kMaxL + 1];
int l, len[kMaxN + 1];
Hash hash[kMaxL + 1][kMaxL + 1], rec[kMaxN + 1];
int seq[kMaxN + 1];

int main() {
	scanf("%s", pat + 1);
	l = strlen(pat + 1);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", buf[i] + 1);
		for (int j = 1, k = strlen(buf[i] + 1); j <= k; ++ j)
			rec[i] = rec[i] * kSeed + buf[i][j];
		len[i] = strlen(buf[i] + 1);
	}
	for (int i = 1; i <= l; ++ i)
		for (int j = i; j <= l; ++ j)
			hash[i][j] = hash[i][j - 1] * kSeed + pat[j];
	dp[0][0] = 1;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j <= l; ++ j)
			if (dp[i][j]) {
				dp[i + 1][j] = min(kInf, dp[i + 1][j] + dp[i][j]);
				int st = j + 1, ed = j + len[i + 1];
				if (ed <= l && hash[st][ed] == rec[i + 1])
					dp[i + 1][ed] = min(kInf, dp[i + 1][ed] + dp[i][j]);
			}
	if (!dp[n][l]) puts("NIE");
	else {
		printf("%d\n", dp[n][l]);
		int i = n, j = l;
		while (i) {
			if (dp[i - 1][j]) -- i;
			else {
				seq[++ seq[0]] = i;
				j -= len[i];
				-- i;
			}
		}
		for (int i = seq[0]; i >= 1; -- i) printf("%d\n", seq[i]);
	}
	return 0;
}
