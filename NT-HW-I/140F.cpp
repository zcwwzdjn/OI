#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxN = 200000, kMaxK = 10;
int n, k;

struct Point {
	int x, y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
	bool operator < (const Point &t) const {
		return (x != t.x ? x < t.x : y < t.y);
	}
} p[kMaxN];

set<Point> ans, rec;
Point t;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		rec.insert(p[i]);
	}
	if (k >= n) {
		puts("-1");
		return 0;
	}
	sort(p, p + n);
	for (int i = 0; i < n; ++ i)
		if (abs(i - (n - 1 - i)) <= k) {
			int tmp = 0;
			for (int j = 0; j < n; ++ j) {
				Point t(p[i].x * 2 - p[j].x, p[i].y * 2 - p[j].y);
				tmp += !rec.count(t);
				if (tmp > k) break;
			}
			if (tmp <= k) ans.insert(Point(p[i].x * 2, p[i].y * 2));
		}
	for (int i = 0; i <= n; ++ i)
		if (abs(i - (n - i)) <= k) {
			if (i >= (n - i)) {
				for (int m = 0; m < min(n - i, k + 1); ++ m)
					for (int j = 0; j < min(i, k + 1); ++ j) if (m + j <= k) {
						Point t(p[j].x + p[n - 1 - m].x, p[j].y + p[n - 1 - m].y);
						int tmp = j + m;
						for (int l = j + 1, r = n - 1 - m - 1; l <= r; ) {
							Point u(t.x - p[l].x, t.y - p[l].y);
						   	while (r > l && (p[r].x > u.x || (p[r].x == u.x && p[r].y > u.y))) -- r, ++ tmp;
							if (l == r || p[r].x != u.x || p[r].y != u.y) ++ tmp;
							else -- r;
							++ l;
							if (tmp > k) break;
						}
						if (tmp <= k) ans.insert(t);
					}
			}
			else {
				for (int m = 0; m < min(i, k + 1); ++ m)
					for (int j = 0; j < min(n - i, k + 1); ++ j) if (m + j <= k) {
						Point t(p[n - 1 - j].x + p[m].x, p[n - 1 - j].y + p[m].y);
						int tmp = j + m;
						for (int l = m + 1, r = n - 1 - j - 1; l <= r; ) {
							Point u(t.x - p[l].x, t.y - p[l].y);
							while (r > l && (p[r].x > u.x || (p[r].x == u.x && p[r].y > u.y))) -- r, ++ tmp;
							if (l == r || p[r].x != u.x || p[r].y != u.y) ++ tmp;
							else -- r;
							++ l;
							if (tmp > k) break;
						}
						if (tmp <= k) ans.insert(t);
					}
			}
		}
	printf("%d\n", ans.size());
	for (set<Point>::iterator it = ans.begin(); it != ans.end(); ++ it) printf("%.8lf %.8lf\n", it->x * 0.5, it->y * 0.5);
	return 0;
}
