/*
 * $File: sie.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a graph, find pairs of vertices,
 *   the shortest path between which is exacly
 *   the road between them.
 *
 * Solution:
 *   Simple graph problem. Just Floyd.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 200;
int n, d[kMaxN][kMaxN];
bool e[kMaxN][kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j) scanf("%d", &d[i][j]);
	for (int k = 0; k < n; ++ k)
		for (int i = 0; i < n - 1; ++ i) if (i != k)
			for (int j = i + 1; j < n; ++ j) if (j != k && j != i)
				if (d[i][k] + d[k][j] <= d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					e[i][j] = true;
				}
	for (int i = 0; i < n - 1; ++ i)
		for (int j = i + 1; j < n; ++ j)
			if (!e[i][j]) printf("%d %d\n", i + 1, j + 1);
	return 0;
}
