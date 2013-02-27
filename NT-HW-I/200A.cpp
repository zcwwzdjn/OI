#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 2000, kMaxM = 2000;
int n, m, q;
bool rev;

struct DS {
	int root[kMaxM + 2];
	void init() {
		for (int i = 0; i <= m + 1; ++ i) root[i] = i;
	}
	int find(int x) {
		return (x == root[x] ? x : root[x] = find(root[x]));
	}
} ds_l[kMaxN + 1], ds_r[kMaxN + 1];

bool Cmp(int x0, int y0, int x1, int y1) {
	if (!rev)
		return (x0 != x1 ? x0 < x1 : y0 < y1);
	else
		return (y0 != y1 ? y0 < y1 : x0 < x1);
}

void Find(int &x, int &y) {
	int dis = kInf;
	int rx, ry;
	for (int d = 0; d <= dis; ++ d) {
		int nx, ny, nd;
		if (x - d >= 1) {
			nx = x - d;
			ny = ds_l[nx].find(y);
			nd = d + (y - ny);
			if (ny >= 1 && (nd < dis || (nd == dis && Cmp(nx, ny, rx, ry)))) {
				rx = nx, ry = ny, dis = nd;
			}
			ny = ds_r[nx].find(y);
			nd = d + (ny - y);
			if (ny <= m && (nd < dis || (nd == dis && Cmp(nx, ny, rx, ry)))) {
				rx = nx, ry = ny, dis = nd;
			}
		}
		if (x + d <= n) {
			nx = x + d;
			ny = ds_l[nx].find(y);
			nd = d + (y - ny);
			if (ny >= 1 && (nd < dis || (nd == dis && Cmp(nx, ny, rx, ry)))) {
				rx = nx, ry = ny, dis = nd;
			}
			ny = ds_r[nx].find(y);
			nd = d + (ny - y);
			if (ny <= m && (nd < dis || (nd == dis && Cmp(nx, ny, rx, ry)))) {
				rx = nx, ry = ny, dis = nd;
			}
		}
	}
	x = rx, y = ry;
	ds_l[x].root[y] = y - 1;
	ds_r[x].root[y] = y + 1;
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	rev = (n > m);
	if (rev) swap(n, m);
	for (int i = 1; i <= n; ++ i) {
		ds_l[i].init();
		ds_r[i].init();
	}
	for (int x, y; q --; ) {
		scanf("%d%d", &x, &y);
		if (rev) swap(x, y);
		Find(x, y);
		if (rev) swap(x, y);
		printf("%d %d\n", x, y);
	}
	return 0;
}
