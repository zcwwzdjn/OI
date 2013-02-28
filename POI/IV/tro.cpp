/*
 * $File: tro.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a graph, and each edge is either
 *   red or black, find the numbers of triangles
 *   that all 3 edges are the same color.
 *
 * Solution:
 *   We can count the number of triangles that
 *   not all edges are the same color. Consider a
 *   vertex with red degree a, black degree b, then
 *   we can add a * b to the answer. However,
 *   it's not correct. Actually all triangles are
 *   counted twice. Just divide the sum by 2,
 *   and the real answer is C(N, 3) - sum.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int n, m, d[kMaxN];

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		++ d[u], ++ d[v];
	}
	int res = n * (n - 1) * (n - 2) / 3;
	for (int i = 0; i < n; ++ i) res -= d[i] * (n - 1 - d[i]);
	res >>= 1;
	printf("%d\n", res);
	return 0;
}
