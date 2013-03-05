/*
 * $File: wie.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a polygon which has been cut into
 *   some triangles, find a triangle to cross
 *   as many triangles as possible.
 *
 * Solution:
 *   Dynamic programming. Firstly we can turn
 *   the original problem to: given a tree, find
 *   3 vertices and let the nodes among them
 *   maximal. Then do a simple dp.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;
const int kMaxN = 1000;
int n, m;
map<Pair, int> rec;

#define MP make_pair

const int kInf = 0x3f3f3f3f;
const int kMaxV = kMaxN - 2, kMaxE = (kMaxN - 3) * 2;
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE];
int h[kMaxV], res;

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void AddPair(int u, int v) {
	AddEdge(u, v);
	AddEdge(v, u);
}

void Dfs0(int u, int p) {
	for (int now = begin[u], v; now != -1; now = next[now])
		if ((v = end[now]) != p) {
			Dfs0(v, u);
			h[u] = max(h[u], h[v]);
		}
	++ h[u];
}

void Dfs1(int u, int p, int w) {
	int seq[2];
	seq[0] = seq[1] = 0;
	for (int now = begin[u], v; now != -1; now = next[now])
		if ((v = end[now]) != p) {
			if (h[v] > seq[0]) {
				seq[1] = seq[0];
				seq[0] = h[v];
			}
			else if (h[v] > seq[1])
				seq[1] = h[v];
		}
	res = max(res, w + 1);
	res = max(res, seq[0] + w + 1);
	res = max(res, seq[0] + seq[1] + w + 1);
	for (int now = begin[u], v; now != -1; now = next[now])
		if ((v = end[now]) != p) {
			if (h[v] != seq[0]) Dfs1(v, u, max(w, seq[0]) + 1);
			else Dfs1(v, u, max(w, seq[1]) + 1);
		}
}

int main() {
	scanf("%d", &n);
	cnt = 0, memset(begin, -1, sizeof(begin));
	for (int i = 0; i < n - 2; ++ i) {
		static int seq[3];
		for (int j = 0; j < 3; ++ j) scanf("%d", &seq[j]);
		sort(seq, seq + 3);
		for (int j = 0; j < 2; ++ j)
			for (int k = j + 1; k < 3; ++ k)
				if (rec.count(MP(seq[j], seq[k]))) AddPair(m, rec[MP(seq[j], seq[k])]);
		for (int j = 0; j < 2; ++ j)
			for (int k = j + 1; k < 3; ++ k)
				rec[MP(seq[j], seq[k])] = m;
		++ m;
	}
	Dfs0(0, -1);
	Dfs1(0, -1, 0);
	printf("%d\n", res);
	return 0;
}
