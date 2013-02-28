/*
 * $File: ali.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a start triple and a final
 *   triple, and some change rules, find
 *   the minimal steps to reach final state
 *   from start state.
 *
 * Solution:
 *   Simple bfs.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> to[512];
int start, final, dis[512];
int q[512], qh, qt;

int Read() {
	int res = 0;
	for (int i = 0, x; i < 3; ++ i) {
		scanf("%d", &x);
		res |= x << (i * 3);
	}
	return res;
}

#define G(a, b, c) ((a) << 0 | (b) << 3 | (c) << 6)

void Bfs() {
	memset(dis, 0x3f, sizeof(dis));
	qh = qt = 0;
	dis[q[qt ++] = start] = 0;
	while (qh < qt) {
		int u = q[qh ++];
		int A = u >> 0 & 7;
		int B = u >> 3 & 7;
		int C = u >> 6 & 7;
		for (int a = 0; a <= A; ++ a)
			for (int b = 0; b <= B; ++ b)
				for (int c = 0; c <= C; ++ c) {
					int msk = G(a, b, c);
					for (vector<int>::iterator it = to[msk].begin(); it != to[msk].end(); ++ it) {
						int _a = A - a + ((*it) >> 0 & 7);
						int _b = B - b + ((*it) >> 3 & 7);
						int _c = C - c + ((*it) >> 6 & 7);
						if (_a <= 7 && _b <= 7 && _c <= 7) {
							int v = G(_a, _b, _c);
							if (dis[v] > dis[u] + 1) {
								dis[v] = dis[u] + 1;
								q[qt ++] = v;
							}
						}
					}
				}
	}
}

int main() {
	int T;
	for (scanf("%d", &T); T --; ) {
		for (int msk = 0; msk < 512; ++ msk) to[msk].clear();
		start = Read(), final = Read();
		int t;
		for (scanf("%d", &t); t --; ) {
			int u = Read(), v = Read();
			to[u].push_back(v);
		}
		Bfs();
		int res = 0x3f3f3f3f;
		int A = final >> 0 & 7;
		int B = final >> 3 & 7;
		int C = final >> 6 & 7;
		for (int a = A; a <= 7; ++ a)
			for (int b = B; b <= 7; ++ b)
				for (int c = C; c <= 7; ++ c) {
					int msk = G(a, b, c);
					res = min(res, dis[msk]);
				}
		if (res != 0x3f3f3f3f) printf("%d\n", res);
		else printf("NIE\n");
	}
	return 0;
}
