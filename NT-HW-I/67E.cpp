#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int n;

inline int sgn(double x) {
	if (fabs(x) < 1E-7) return 0;
	if (x > 0.0) return 1;
	return -1;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x_, double y_) : x(x_), y(y_) {}
} pnt[kMaxN];

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
	return (Vector(a.x + b.x, a.y + b.y));
}

Vector operator - (const Vector &a, const Vector &b) {
	return (Vector(a.x - b.x, a.y - b.y));
}

double det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%lf%lf", &pnt[i].x, &pnt[i].y);
	for (int i = 2; i < n; ++ i) pnt[i].y -= pnt[0].y;
	pnt[0].y = pnt[1].y = 0;
	for (int i = 2; i < n; ++ i) pnt[i].y = abs(pnt[i].y);
	if (pnt[0].x > pnt[1].x) {
		swap(pnt[0], pnt[1]);
		reverse(pnt + 2, pnt + n);
	}
	double lb = pnt[0].x, rb = pnt[1].x;
	for (int i = 2; i < n - 1; ++ i) {
		int j = i + 1;
		Vector v = pnt[j] - pnt[i];
		if (sgn(v.y) == 0) {
			if (sgn(v.x) > 0) {
				printf("0\n");
				return 0;
			}
		}
		else {
			double pos = pnt[i].x - v.x / v.y * pnt[i].y;
			if (sgn(det(v, Point(rb, 0.0) - pnt[i])) < 0) rb = min(rb, pos);
			if (sgn(det(v, Point(lb, 0.0) - pnt[i])) < 0) lb = max(lb, pos);
			if (sgn(lb - rb) > 0) {
				printf("0\n");
				return 0;
			}
		}
	}
	int res = max(0, (int)(floor(rb) + 1E-7) - (int)(ceil(lb) + 1E-7) + 1);
	printf("%d\n", res);
	return 0;
}
