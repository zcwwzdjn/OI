/*
 * $File: lam.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given points in a cartesian coordinate
 *   system, you can connect two points and
 *   the angle is in [-45, 45], and find the
 *   minimal number of fragments.
 *
 * Solution:
 *   Rotate all points by 45, then the new
 *   problem is a simple LIS.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 30000, kInf = 0x3f3f3f3f;
int n, res;
int lis[kMaxN + 1];

struct Point {
	int x, y;
	bool operator < (const Point &t) const {
		if (x != t.x) return (x < t.x);
		return (y < t.y);
	}
} pnt[kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &pnt[i].x, &pnt[i].y);
		int x = pnt[i].x - pnt[i].y;
		int y = pnt[i].x + pnt[i].y;
		pnt[i].x = x, pnt[i].y = y;
	}
	for (int i = 1; i <= n; ++ i) lis[i] = -kInf;
	lis[0] = kInf;
	sort(pnt, pnt + n);
	for (int i = 0; i < n; ++ i) {
		int lb = 0, rb = n + 1;
		while (lb + 1 < rb) {
			int mid = (lb + rb) >> 1;
			if (pnt[i].y < lis[mid]) lb = mid;
			else rb = mid;
		}
		res = max(res, lb + 1);
		lis[lb + 1] = max(lis[lb + 1], pnt[i].y);
	}
	printf("%d\n", res);
	return 0;
}
