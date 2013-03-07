/*
 * $File: pro.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some rectangles, find the number
 *   of blocks.
 *
 * Solution:
 *   Simple implementation. Use disjoint set
 *   to maintain the relationship between 
 *   rectangles.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 7000;
int n, x1[kMaxN], y1[kMaxN], x2[kMaxN], y2[kMaxN];
int root[kMaxN];

int Root(int x) {
	return (x == root[x] ? x : root[x] = Root(root[x]));
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
	for (int i = 0; i < n; ++ i) root[i] = i;
	int res = n;
	for (int i = 1; i < n; ++ i)
		for (int j = 0; j < i; ++ j) {
			int u = Root(i), v = Root(j);
			if (u != v) {
				int a = min(x2[i], x2[j]) - max(x1[i], x1[j]);
				int b = min(y2[i], y2[j]) - max(y1[i], y1[j]);
				if (a >= 0 && b >= 0 && a + b > 0) root[u] = v, -- res;
			}
		}
	printf("%d\n", res);
	return 0;
}
