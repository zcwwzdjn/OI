/*
 * $File: kul.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a circle with N boxes, and no more
 *   than N balls are put in these boxes. In each
 *   move we can move a ball from a box to its
 *   neighbors. Find the minimal cost to make in each
 *   box there's no more than 1 ball.
 *
 * Solution:
 *   Minimum cost flow. The way to build the graph
 *   is obvious.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int n;

const int kInf = 0x3f3f3f3f;
const int kMaxV = kMaxN + 2, kMaxE = (kMaxN * 2 + kMaxN * 2) * 2;
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cap[kMaxE], cost[kMaxE];
int sv, tv, dis[kMaxV], pre[kMaxV], mincost;
bool vis[kMaxV];
int q[kMaxV], qh, qt;

void AddEdge(int u, int v, int c, int w) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cap[cnt] = c;
	cost[cnt ++] = w;
}

void AddPair(int u, int v, int c, int w) {
	AddEdge(u, v, c, w);
	AddEdge(v, u, 0, -w);
}

bool Spfa() {
	memset(dis, 0x3f, sizeof(dis));
	qh = qt = 0;
	dis[sv] = 0;
	q[qt ++] = sv, vis[sv] = true;
	while (qh != qt) {
		int u = q[qh ++];
		if (qh >= kMaxV) qh -= kMaxV;
		vis[u] = false;
		for (int now = begin[u], v; now != -1; now = next[now])
			if (cap[now] && dis[v = end[now]] > dis[u] + cost[now]) {
				dis[v] = dis[u] + cost[now];
				pre[v] = now;
				if (!vis[v] && dis[v] < dis[tv]) {
					q[qt ++] = v;
					if (qt >= kMaxV) qt -= kMaxV;
					vis[v] = true;
				}
			}
	}
	return (dis[tv] != kInf);
}

void DoAug() {
	for (int i = tv; i != sv; i = end[pre[i] ^ 1]) {
		-- cap[pre[i]];
		++ cap[pre[i] ^ 1];
	}
	mincost += dis[tv];
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	sv = n, tv = n + 1;
	for (int i = 0, x; i < n; ++ i) {
		scanf("%d", &x);
		if (x) AddPair(sv, i, x, 0);
		AddPair(i, tv, 1, 0);
	}
	for (int i = 1; i < n - 1; ++ i) {
		AddPair(i, i + 1, kInf, 1);
		AddPair(i, i - 1, kInf, 1);
	}
	AddPair(0, 1, kInf, 1), AddPair(0, n - 1, kInf, 1);
	AddPair(n - 1, n - 2, kInf, 1), AddPair(n - 1, 0, kInf, 1);
	while (Spfa()) DoAug();
	printf("%d\n", mincost);
	return 0;
}
