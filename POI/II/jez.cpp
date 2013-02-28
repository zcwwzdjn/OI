/*
 * $File: jez.cpp
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

const int kMaxN = 1000000;
int T, N;
bool vis[kMaxN];
int pre[kMaxN], way[kMaxN];
int q[kMaxN], qh, qt;
int seq[kMaxN], seq_idx;

void Print(int x) {
	seq_idx = 0;
	while (x) {
		seq[seq_idx ++] = way[x];
		x = pre[x];
	}
	for (int i = seq_idx - 1; i >= 0; -- i) putchar('0' + seq[i]);
}

void Solve() {
	memset(vis, false, sizeof(vis));
	qh = qt = 0;
	pre[0] = -1, vis[0] = true, q[qt ++] = 0;
	while (qh < qt) {
		int u = q[qh ++];
		for (int i = (u == 0); i < 2; ++ i) {
			int v = (u * 10 + i) % N;
			if (v == 0) {
				Print(u);
				if (i == 0) puts("0");
				else puts("1");
				return;
			}
			if (!vis[v]) {
				vis[v] = true;
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
