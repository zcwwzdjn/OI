/*
 * $File: nie.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a 3 * N chess board, to put as
 *   many knights as possible on it.
 *
 * Solution:
 *   Dynamic programming. Record the last two
 *   columns' status in dp state. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
int n, mask[kMaxN];
int f[2][8][8], g[2][8][8];
bool ban[8][8][8];
int cnt[8];

int main() {
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i) {
		scanf("%d", &x);
		-- x;
		mask[i] = 7;
		if (x >= 0) mask[i] ^= 1 << x;
	}
	for (int i = 0; i < 8; ++ i)
		for (int j = 0; j < 8; ++ j)
			for (int k = 0; k < 8; ++ k) {
				if (k >> 0 & 1) {
					if ((i >> 1 & 1) || (j >> 2 & 1)) ban[i][j][k] = true;
				}
				if (k >> 1 & 1) {
					if ((i >> 0 & 1) || (i >> 2 & 1)) ban[i][j][k] = true;
				}
				if (k >> 2 & 1) {
					if ((i >> 1 & 1) || (j >> 0 & 1)) ban[i][j][k] = true;
				}
			}
	for (int i = 0; i < 8; ++ i) cnt[i] = __builtin_popcount(i);
	int des = 0, src = 1;
	memset(f[des], -0x3f, sizeof(f[des]));
	f[des][0][0] = 0, g[des][0][0] = 1;
	for (int i = 0; i < n; ++ i) {
		des ^= 1, src ^= 1;
		memset(f[des], -0x3f, sizeof(f[des]));
		memset(g[des], 0, sizeof(g[des]));
		for (int a = 0; a < 8; ++ a)
			for (int b = 0; b < 8; ++ b)
				if (f[src][a][b] >= 0)
					for (int c = mask[i]; c >= 0; c = (c > 0 ? ((c - 1) & mask[i]) : -1))
						if (!ban[a][b][c]) {
							int d = cnt[c];
							if (f[src][a][b] + d > f[des][b][c]) {
								f[des][b][c] = f[src][a][b] + d;
								g[des][b][c] = g[src][a][b];
							}
							else if (f[src][a][b] + d == f[des][b][c])
								g[des][b][c] += g[src][a][b];
						}
	}
	int ans = 0, sum = 1;
	for (int a = 0; a < 8; ++ a)
		for (int b = 0; b < 8; ++ b)
			if (f[des][a][b] > ans) {
				ans = f[des][a][b];
				sum = g[des][a][b];
			}
			else if (f[des][a][b] == ans)
				sum += g[des][a][b];
	printf("%d %d\n", ans, sum);
	return 0;
}
