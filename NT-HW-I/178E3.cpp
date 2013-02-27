#include <cmath>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;
const int kMaxN = 2000, kMinSize = 50;
const double kCircleDiff = 1.4, kEps = 1E-8;
const int kFx[4] = {-1, 1, 0, 0}, kFy[4] = {0, 0, -1, 1};
int n, bmp[kMaxN][kMaxN], cnt[kMaxN][kMaxN], tot[kMaxN][kMaxN];
int dfn[kMaxN][kMaxN], dcnt;
Pair q[kMaxN * kMaxN];
int qh, qt;
int ans[2];

#define INR(x, y) ((x) >= 0 && (x) < n && (y) >= 0 && (y) < n)

int nextInt() {
	char c;
	for (c = getchar(); c < '0' || c > '9'; c = getchar());
	int res = c - '0';
	while (true) {
		c = getchar();
		if (c < '0' || c > '9') break;
		res = res * 10 + c - '0';
	}
	return res;
}

int Check() {
	int minx = INT_MAX, maxx = INT_MIN;
	int miny = INT_MAX, maxy = INT_MIN;
	for (int i = 0; i < qt; ++ i) {
		int x = q[i].first, y = q[i].second;
		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
	}
	double cx = (minx + maxx - 1) * 0.5;
	double cy = (miny + maxy - 1) * 0.5;
	double mind = INT_MAX, maxd = INT_MIN;
	for (int i = minx + 1; i < maxx; ++ i) {
		int l = miny, r = maxy;
		while (l <= maxy && dfn[i][l] != dcnt) ++ l;
		while (r >= miny && dfn[i][r] != dcnt) -- r;
		double dx, dy, d;
		if (l <= maxy) {
			dx = i - cx, dy = l - cy;
			d = sqrt(dx * dx + dy * dy);
			mind = min(mind, d), maxd = max(maxd, d);
		}
		if (r >= miny) {
			dx = i - cx, dy = r - cy;
			d = sqrt(dx * dx + dy * dy);
			mind = min(mind, d), maxd = max(maxd, d);
		}
	}
	return (maxd / mind > kCircleDiff + kEps);
}

int main() {
	n = nextInt();
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j) bmp[i][j] = nextInt();
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			for (int x = i - 2; x <= i + 2; ++ x)
				for (int y = j - 2; y <= j + 2; ++ y)
					if (INR(x, y)) cnt[i][j] += bmp[x][y], ++ tot[x][y];
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			if (cnt[i][j] > tot[i][j] / 2) bmp[i][j] = 1;
			else bmp[i][j] = 0;
	for (int i = 2; i < n - 2; ++ i)
		for (int j = 2; j < n - 2; ++ j)
			if (bmp[i][j] && !dfn[i][j]) {
				qh = qt = 0;
				++ dcnt;
				q[qt ++] = make_pair(i, j);
				dfn[i][j] = dcnt;
				while (qh < qt) {
					Pair u = q[qh ++];
					for (int d = 0; d < 4; ++ d) {
						Pair v(u.first + kFx[d], u.second + kFy[d]);
						if (INR(v.first, v.second) && bmp[v.first][v.second] && !dfn[v.first][v.second]) {
							q[qt ++] = v;
							dfn[v.first][v.second] = dcnt;
						}
					}
				}
				if (qt >= kMinSize) ++ ans[Check()];
			}
	printf("%d %d\n", ans[0], ans[1]);
	return 0;
}
