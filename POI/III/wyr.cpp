/*
 * $File: wyr.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given string x and y, and a set of strings,
 *   we can choose some strings from the set,
 *   and add them to x or y. Try in least moves to
 *   make x and y identical.
 *
 * Solution:
 *   Dynamic programming. Let DP[i][j] be the state
 *   when longer string ends with i, and the length
 *   is larger by j, the minimal moves.
 *   Then use a bfs to dp.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 42, kInf = 0x3f3f3f3f;
int n, sz[kMaxN];
char buf[kMaxN][2048];

bool Check(int i, int is, int j, int js) {
	int l = min(sz[i] - is, sz[j] - js);
	for (int k = 0; k < l; ++ k)
		if (buf[i][is + k] != buf[j][js + k]) return false;
	return true;
}

#define A(i, is, j, js) ((sz[i] - (is) > sz[j] - (js)) ? (i) : (j))
#define B(i, is, j, js) (abs((sz[i] - (is)) - (sz[j] - (js))))

int dis[kMaxN][2048];
struct Node {
	int a, b;
	Node() {}
	Node(int a_, int b_) : a(a_), b(b_) {}
} q[kMaxN * 2048];
int qh, qt;

int Solve(int a, int b) {
	memset(dis, 0x3f, sizeof(dis));
	q[qt ++] = Node(a, b);
	dis[a][b] = 0;
	while (qh < qt) {
		Node u = q[qh ++];
		if (u.b == 0) return dis[u.a][u.b];
		for (int i = 2; i < n; ++ i)
			if (Check(u.a, sz[u.a] - u.b, i, 0)) {
				Node v(A(u.a, sz[u.a] - u.b, i, 0), B(u.a, sz[u.a] - u.b, i, 0));
				if (dis[v.a][v.b] == kInf) {
					dis[v.a][v.b] = dis[u.a][u.b] + 1;
					q[qt ++] = v;
				}
			}
	}
	return kInf;
}

int main() {
	scanf("%d", &n);
	n += 2;
	for (int i = 0; i < n; ++ i) scanf("%d%s", &sz[i], buf[i]);
	if (!Check(0, 0, 1, 0)) puts("NIE");
	else {
		int a = A(0, 0, 1, 0);
		int b = B(0, 0, 1, 0);
		int r = Solve(a, b);
		if (r != kInf) printf("%d\n", r);
		else puts("NIE");
	}
	return 0;
}
