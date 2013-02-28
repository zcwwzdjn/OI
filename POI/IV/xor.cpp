/*
 * $File: xor.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a xor net, and a range of tests,
 *   find the number of tests that output 1.
 *
 * Solution:
 *   Firstly we can bfs the net to find if
 *   a input has effect on the output. Then we
 *   can do a dynamic programming. Let
 *   DP[L][0/1][0/1][0/1] be the state when we
 *   use first L digits and if it's on the lower
 *   bound and if it's on the upper bound and
 *   the xor result.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100, kMaxM = 3000;
const int kMaxV = kMaxN + kMaxM, kMaxE = kMaxM * 2;
int n, m, q[kMaxV], qh, qt;
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE];
int ind[kMaxV];
bool rec[kMaxV][kMaxN];
int dp[2][2][2][2];
char lower[128], upper[128];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d%d", &n, &m, &q[0]);
	q[0] += n - 1;
	for (int u = n; u < n + m; ++ u)
		for (int i = 0, v; i < 2; ++ i) {
			scanf("%d", &v);
			if (v < 0) v = -v - 1;
			else v += n - 1;
			AddEdge(u, v);
			++ ind[v];
		}
	++ qt;
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (!(-- ind[v = end[now]])) q[qt ++] = v;
	}
	for (int i = 0; i < n; ++ i) rec[i][i] = true;
	for (int i = n + m - 1; i >= 0; -- i) {
		int u = q[i];
		for (int now = begin[u], v; now != -1; now = next[now]) {
			v = end[now];
			for (int j = 0; j < n; ++ j) rec[u][j] ^= rec[v][j];
		}
	}
	scanf("%s%s", lower, upper);
	int p = q[0];
	int des = 0, src = 1;
	dp[des][1][1][0] = 1;
	for (int i = 0; i < n; ++ i) {
		des ^= 1, src ^= 1;
		memset(dp[des], 0, sizeof(dp[des]));
		for (int lo = 0; lo < 2; ++ lo)
			for (int up = 0; up < 2; ++ up)
				for (int j = 0; j < 2; ++ j)
					if (dp[src][lo][up][j]) {
						int lb = lo ? lower[i] - '0' : 0;
						int rb = up ? upper[i] - '0' : 1;
						for (int k = lb; k <= rb; ++ k) {
							int lo_ = lo & (k == lower[i] - '0');
							int up_ = up & (k == upper[i] - '0');
							int j_ = j ^ (k & rec[p][i]);
							dp[des][lo_][up_][j_] += dp[src][lo][up][j];
						}
					}
	}
	int res = 0;
	for (int lo = 0; lo < 2; ++ lo)
		for (int up = 0; up < 2; ++ up)
			res += dp[des][lo][up][1];
	printf("%d\n", res);
	return 0;
}
