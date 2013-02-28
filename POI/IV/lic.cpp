/*
 * $File: lic.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given 2 lists of words of length N,
 *   for each 1 <= i <= N we can choose a
 *   word from either list, find the number
 *   of ways to construct palindromes.
 *
 * Solution:
 *   Dynamic programming.
 *   Let DP[L][R][0/1][0/1][C] be the number
 *   of ways when we choose first L words and
 *   last R words, the longer on is the first
 *   or the last, the string is chosen from 
 *   which list, and the rest of the longer one's
 *   length.
 *   Simple dp, but many details.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 30, kMaxL = 400;
int n, len[2][kMaxN + 1];
char pat[2][kMaxN + 1][kMaxL + 1];
int dp[kMaxN + 2][kMaxN + 2][2][2][kMaxL + 1];

bool Check(int p_bel, int p, int pl, int q_bel, int q, int ql, int c) {
	int qr = ql + c - 1;
	int pr = pl + c - 1;
	while (pl <= pr) {
		if (pat[p_bel][p][pl] != pat[q_bel][q][qr]) return false;
		++ pl, -- qr;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int bel = 0; bel < 2; ++ bel)
		for (int i = 1; i <= n; ++ i) {
			scanf("%s", pat[bel][i]);
			len[bel][i] = strlen(pat[bel][i]);
		}
	dp[0][n + 1][0][0][0] = 1;
	for (int step = n + 1; step > 1; -- step)
		for (int l = 0; l + step <= n + 1; ++ l) {
			int r = l + step;
			for (int side = 0; side < 2; ++ side) {
				int p = side ? r : l;
				for (int p_bel = 0; p_bel < 2; ++ p_bel)
					for (int c = 0; c <= len[p_bel][p]; ++ c)
						if (dp[l][r][side][p_bel][c] > 0) {
							int q = side ? l + 1 : r - 1;
							for (int q_bel = 0; q_bel < 2; ++ q_bel) {
								if (len[q_bel][q] < c || (len[q_bel][q] == c && side == 0)) {
									if (side == 0 && Check(p_bel, p, len[p_bel][p] - c, q_bel, q, 0, len[q_bel][q])) 
										dp[min(p, q)][max(p, q)][side][p_bel][c - len[q_bel][q]] += dp[l][r][side][p_bel][c];
									if (side == 1 && Check(p_bel, p, c - len[q_bel][q], q_bel, q, 0, len[q_bel][q]))
										dp[min(p, q)][max(p, q)][side][p_bel][c - len[q_bel][q]] += dp[l][r][side][p_bel][c];

								}
								else {
									if (side == 0 && Check(p_bel, p, len[p_bel][p] - c, q_bel, q, len[q_bel][q] - c, c))
										dp[min(p, q)][max(p, q)][side ^ 1][q_bel][len[q_bel][q] - c] += dp[l][r][side][p_bel][c];
									if (side == 1 && Check(p_bel, p, 0, q_bel, q, 0, c))
										dp[min(p, q)][max(p, q)][side ^ 1][q_bel][len[q_bel][q] - c] += dp[l][r][side][p_bel][c];
								}
							}
						}
			}
		}
	int res = 0;
	for (int l = 0; l + 1 <= n + 1; ++ l) {
		int r = l + 1;
		for (int side = 0; side < 2; ++ side) {
			int p = side ? r : l;
			for (int p_bel = 0; p_bel < 2; ++ p_bel)
				for (int c = 0; c <= len[p_bel][p]; ++ c)
					if (dp[l][r][side][p_bel][c] > 0) {
						if (side == 0 && Check(p_bel, p, len[p_bel][p] - c, p_bel, p, len[p_bel][p] - c, c))
							res += dp[l][r][side][p_bel][c];
						if (side == 1 && Check(p_bel, p, 0, p_bel, p, 0, c))
							res += dp[l][r][side][p_bel][c];
					}
		}
	}
	printf("%d\n", res);
	return 0;
}
