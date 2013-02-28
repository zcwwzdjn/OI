/*
 * $File: jed.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a positive integer N, find the
 *   smallest positive integer, which only 
 *   has digit 0 and 1, and is a product of
 *   N.
 *
 * Solution:
 *   Graph theory. Suppose that we start from 0.
 *   Then in each move we can use 0 or 1, and
 *   if current position is u, we go to 
 *   (u * 10 + 0) % N or (u * 10 + 1) % N.
 *   So just do a bfs.
 */

#include <cstdio>
#include <cstring>

const int kMaxN = 20000;
int T, N;
int dis[kMaxN], pre[kMaxN], way[kMaxN];
int q[kMaxN], qh, qt;

void Print(int x) {
	if (x == 0) return;
	Print(pre[x]);
	printf("%d", way[x]);
}

void Solve() {
	memset(dis, 0x3f, sizeof(dis));
	qh = qt = 0;
	pre[0] = -1, dis[0] = 0, q[qt ++] = 0;
	while (qh < qt) {
		int u = q[qh ++];
		for (int i = (u == 0); i < 2; ++ i) {
			int v = (u * 10 + i) % N;
			if (v == 0) {
				Print(u);
				printf("%d\n", i);
				return;
			}
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				pre[v] = u;
				way[v] = i;
				q[qt ++] = v;
			}
		}
	}
}


int main() {
	for (scanf("%d", &T); T --; ) {
		scanf("%d", &N);
		Solve();
	}
	return 0;
}
