#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 500;
int n;
double h, f;

inline int sgn(double x) {
	if (fabs(x) < 1E-7) return 0;
	if (x > 0.0) return 1;
	return -1;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x_, double y_) : x(x_), y(y_) {}
};

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
	return Vector(a.x + b.x, a.y + b.y);
}

Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y);
}

double det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}

double len(const Vector &v) {
	return (sqrt(v.x * v.x + v.y * v.y));
}

struct Seg {
	Point l, r;
	Seg() {}
	Seg(const Point &l_, const Point &r_) : l(l_), r(r_) {}
};

struct Trapezoid {
	Seg up, lo;
	Trapezoid() {}
	Trapezoid(const Seg &up_, const Seg &lo_) : up(up_), lo(lo_) {}
} tr[kMaxN * 2];

bool IsIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
	if (sgn(det(b - a, c - a)) * sgn(det(b - a, d - a)) > 0) return false;
	if (sgn(det(d - c, a - c)) * sgn(det(d - c, b - c)) > 0) return false;
	if (sgn(max(a.x, b.x) - min(c.x, d.x)) < 0) return false;
	if (sgn(max(a.y, b.y) - min(c.y, d.y)) < 0) return false;
	if (sgn(max(c.x, d.x) - min(a.x, b.x)) < 0) return false;
	if (sgn(max(c.y, d.y) - min(a.y, b.y)) < 0) return false;
	return true;
}

bool IsIntersect(const Seg &a, const Seg &b) {
	return IsIntersect(a.l, a.r, b.l, b.r);
}

Point CalcIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
	double mat[2][3];
	mat[0][0] = d.x - c.x, mat[0][1] = a.x - b.x, mat[0][2] = a.x - c.x;
	mat[1][0] = d.y - c.y, mat[1][1] = a.y - b.y, mat[1][2] = a.y - c.y;
	for (int i = 0, j = 0, k; i < 2; ++ i, ++ j) {
		for (k = j; k < 2; ++ k)
			if (sgn(mat[k][i]) != 0) break;
		if (k == 2) continue;
		for (int p = 0; p < 3; ++ p) swap(mat[j][p], mat[k][p]);
		double t = mat[j][i];
		for (int p = 0; p < 3; ++ p) mat[j][p] /= t;
		for (k = 0; k < 2; ++ k)
			if (k != j) {
				t = mat[k][i];
				for (int p = 0; p < 3; ++ p) mat[k][p] -= t * mat[j][p];
			}
	}
	return Point(a.x + (b.x - a.x) * mat[1][2], a.y + (b.y - a.y) * mat[1][2]);
}

Point CalcIntersect(const Seg &a, const Seg &b) {
	return CalcIntersect(a.l, a.r, b.l, b.r);
}

double CalcArea(const Trapezoid &t) {
	return ((t.up.r.x - t.up.l.x + t.lo.r.x - t.lo.l.x) * (t.up.r.y - t.lo.r.y) * 0.5);
}

double CalcArea(const Point &a, const Point &b, const Point &c) {
	return (0.5 * fabs(det(b - a, c - a)));
}

double CalcArea(const vector<Point> &hull) {
	int sz = hull.size();
	if (sz == 0) return 0.0;
	vector<int> tmp;
	static int stack[16];
	int stop = 0;
	for (int i = 0, j = 0; i < sz; i = j) {
		while (j < sz && sgn(hull[j].x - hull[i].x) == 0) ++ j;
		while (stop >= 2) {
			Vector v1 = hull[j - 1] - hull[stack[stop - 1]];
			Vector v2 = hull[stack[stop - 1]] - hull[stack[stop - 2]];
			if (sgn(det(v2, v1)) < 0) break;
			-- stop;
		}
		stack[stop ++] = j - 1;
	}
	for (int i = 0; i < stop; ++ i) tmp.push_back(stack[i]);
	stop = 0;
	for (int i = sz - 1, j = sz - 1; i >= 0; i = j) {
		while (j >= 0 && sgn(hull[j].x - hull[i].x) == 0) -- j;
		while (stop >= 2) {
			Vector v1 = hull[j + 1] - hull[stack[stop - 1]];
			Vector v2 = hull[stack[stop - 1]] - hull[stack[stop - 2]];
			if (sgn(det(v2, v1)) < 0) break;
			-- stop;
		}
		stack[stop ++] = j + 1;
	}
	for (int i = 0, st = tmp.front(), ed = tmp.back(); i < stop; ++ i)
		if (stack[i] != st && stack[i] != ed) tmp.push_back(stack[i]);
	sz = tmp.size();
	double res = 0.0;
	for (int i = 1; i < sz - 1; ++ i) res += CalcArea(hull[tmp[0]], hull[tmp[i]], hull[tmp[i + 1]]);
	return res;	
}

bool IsOnOneLine(const Point &a, const Point &b, const Point &c, const Point &d) {
	return (sgn(det(b - a, d - c)) == 0);
}

bool IsOnOneLine(const Seg &a, const Seg &b) {
	return IsOnOneLine(a.l, a.r, b.l, b.r);
}

bool Cmp(const Point &a, const Point &b) {
	return (sgn(a.x - b.x) != 0 ? sgn(a.x - b.x) < 0 : sgn(a.y - b.y) < 0);
}

bool Eq(const Point &a, const Point &b) {
	return (sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0);
}

double CalcCross(const Trapezoid &a, const Trapezoid &b) {
	vector<Point> hull;
	Seg aa[4], bb[4];
	aa[0] = Seg(a.up.l, a.lo.l);
	aa[1] = Seg(a.lo.l, a.lo.r);
	aa[2] = Seg(a.lo.r, a.up.r);
	aa[3] = Seg(a.up.r, a.up.l);
	bb[0] = Seg(b.up.l, b.lo.l);
	bb[1] = Seg(b.lo.l, b.lo.r);
	bb[2] = Seg(b.lo.r, b.up.r);
	bb[3] = Seg(b.up.r, b.up.l);
	for (int i = 0; i < 4; ++ i) {
		for (int j = 0; j < 4; ++ j)
			if (IsIntersect(aa[i], bb[j])) {
				if (IsOnOneLine(aa[i], bb[j])) {
					double x1 = min(aa[i].l.x, aa[i].r.x), x2 = max(aa[i].l.x, aa[i].r.x);
					double x3 = min(bb[i].l.x, bb[i].r.x), x4 = max(bb[i].l.x, bb[i].r.x);
					double lb = max(x1, x3);
					double rb = min(x2, x4);
					hull.push_back(Point(lb, aa[i].l.y));
					hull.push_back(Point(rb, aa[i].l.y));
				}
				else {
					Point t = CalcIntersect(aa[i], bb[j]);
					hull.push_back(t);
				}
			}
	}
	sort(hull.begin(), hull.end(), Cmp);
	hull.resize(unique(hull.begin(), hull.end(), Eq) - hull.begin());
	return CalcArea(hull);
}

int main() {
	scanf("%d%lf%lf", &n, &h, &f);
	for (int i = 0; i < n; ++ i) {
		double l1, r1;
		scanf("%lf%lf", &l1, &r1);
		double l2 = l1 * (f + h) / (f - h);
		double r2 = r1 * (f + h) / (f - h);
		tr[i << 1] = Trapezoid(Seg(Point(l1, h), Point(r1, h)), Seg(Point(l2, -h), Point(r2, -h)));
		tr[i << 1 | 1] = Trapezoid(Seg(Point(l2, h), Point(r2, h)), Seg(Point(l1, -h), Point(r1, -h)));
	}
	double ans = 0.0;
	for (int i = 0; i < (n << 1); ++ i) ans += CalcArea(tr[i]);
	for (int i = 0; i < (n << 1) - 1; ++ i)
		for (int j = i + 1; j < (n << 1); ++ j) ans -= CalcCross(tr[i], tr[j]);
	printf("%.8lf\n", ans);
	return 0;
}
