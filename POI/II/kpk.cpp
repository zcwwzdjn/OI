/*
 * $File: kpk.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a matrix map, you start from A and leave for B,
 *   and you can only go straight or turn right,
 *   find the shortest path.
 *
 * Solution:
 *   Bfs. Define (x, y, d) as state.
 */

#include <cstdio>
#include <cstring>

const int kMaxN = 100, kMaxM = 100, kInf = 0x3f3f3f3f;
const int kFx[4] = {-1, 0, 1, 0}, kFy[4] = {0, 1, 0, -1};
int n, m;
char buf[kMaxN][kMaxM + 1];
int ax, ay, bx, by;
int memo[kMaxN][kMaxM][4];

struct Node {
	int x, y, d;
	Node() {}
	Node(int x_, int y_, int d_) : x(x_), y(y_), d(d_) {}
} q[kMaxN * kMaxM * 4];
int qh, qt, pre[kMaxN][kMaxM][4];

void Print(int x, int y, int d) {
	if (pre[x][y][d] != -1) {
		int p = pre[x][y][d];
		Print(q[p].x, q[p].y, q[p].d);
	}
	printf("%d %d\n", x + 1, y + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) scanf("%s", buf[i]);
	scanf("%d%d%d%d", &ax, &ay, &bx, &by);
	-- ax, -- ay, -- bx, -- by;
	if (buf[ax][ay] == '1' || buf[bx][by] == '1') puts("NIE");
	else {
		memset(memo, 0x3f, sizeof(memo));
		for (int d = 0; d < 4; ++ d) {
			memo[ax][ay][d] = 0;
			q[qt ++] = Node(ax, ay, d);
			pre[ax][ay][d] = -1;
		}
		while (qh < qt) {
			Node u = q[qh ++];
			for (int c = 0; c < 2; ++ c) {
				int d = (u.d + c) & 3;
				Node v(u.x + kFx[d], u.y + kFy[d], d);
				if (v.x < 0 || v.x >= n || v.y < 0 || v.y >= m || buf[v.x][v.y] == '1') continue;
				if (memo[v.x][v.y][v.d] == kInf) {
					memo[v.x][v.y][v.d] = memo[u.x][u.y][u.d] + 1;
					q[qt ++] = v;
					pre[v.x][v.y][v.d] = qh - 1;
				}
			}
		}
		int res = kInf, d;
		for (int c = 0; c < 4; ++ c)
			if (memo[bx][by][c] < res) {
				res = memo[bx][by][c];
				d = c;
			}
		if (res == kInf) puts("NIE");
		else {
			printf("%d\n", res + 1);
			Print(bx, by, d);
		}
	}
	return 0;
}
