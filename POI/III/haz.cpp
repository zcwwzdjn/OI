/*
 * $File: haz.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a graph, find if we can go through all
 *   edges and start at 0 end at N - 1 in all ways.
 *
 * Solution:
 *   First see if we can find a euler path from 0 to N - 1.
 *   If we can not, print a random path. Or we need
 *   to find a circle which does not contain N - 1, 
 *   if we can now, print NIE. Or we can just delete the circle
 *   and print a euler path.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000, kMaxM = 12000;
int n;
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int ind[kMaxN], oud[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

bool used[kMaxM];
void PrintRandomPath(int u) {
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!used[now]) {
			used[now] = true;
			printf("%d ", (v = end[now]) + 1);
			PrintRandomPath(v);
			break;
		}
}

bool CheckEuler() {
	for (int i = 1; i < n - 1; ++ i)
		if (ind[i] != oud[i]) return false;
	if (ind[0] + 1 != oud[0]) return false;
	if (oud[n - 1] + 1 != ind[n - 1]) return false;
	return true;
}

int vis[kMaxN], vcnt;
int pre[kMaxN], pree[kMaxN];
bool FindCircle(int u) {
	vis[u] = vcnt;
	for (int now = begin[u], v; now != -1; now = next[now]) {
		v = end[now];
		if (v == n - 1) continue;
		if (vis[v] == vcnt) {
			used[now] = true;
			while (u != v) {
				used[pree[u]] = true;
				u = pre[u];
			}
			return true;
		}
		if (!vis[v]) {
			pre[v] = u;
			pree[v] = now;
			if (FindCircle(v)) return true;
			vis[v] = 0x3f3f3f3f;
		}
	}
	return false;
}

int seq[kMaxM], m;
void Dfs(int u) {
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!used[now]) {
			used[now] = true;
			seq[m ++] = v = end[now];
			Dfs(v);
		}
}

void PrintEulerPath() {
	Dfs(0);
	for (int i = 0; i < m; ++ i) printf("%d ", seq[i] + 1);
}

bool FindCircle() {
	for (int i = 0; i < n - 1; ++ i) {
		++ vcnt;
		if (!vis[i] && FindCircle(i)) return true;
	}
	return false;
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int i = 0, s; i < n; ++ i) {
		scanf("%d", &s);
		for (int j; s --; ) {
			scanf("%d", &j);
			AddEdge(i, -- j);
			++ oud[i], ++ ind[j];
		}
	}
	if (n > 1 && !CheckEuler()) {
		PrintRandomPath(0);
		puts("0");
	}
	else {
		if (n == 1 || !FindCircle()) puts("NIE");
		else {
			PrintEulerPath();
			puts("0");
		}
	}
	return 0;
}
