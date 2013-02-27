#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const double kEps = 1E-8;

inline int sgn(double x) {
	if (fabs(x) < kEps) return 0;
	if (x > 0.0) return 1;
	return -1;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x_, double y_) : x(x_), y(y_) {}
	void scan() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%lf %lf\n", x, y);
	}
} p, q, w0, w1, m0, m1;

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
	return Vector(a.x + b.x, a.y + b.y);
}

Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y);
}

Vector operator * (const Vector &a, const double &b) {
	return Vector(a.x * b, a.y * b);
}

double dot(const Vector &a, const Vector &b) {
	return (a.x * b.x + a.y * b.y);
}

double det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}

Point CalcFoot(const Point &a, const Point &b, const Point &c) {
	double ratio = dot(a - b, c - b) / dot(c - b, c - b);
	return (b + (c - b) * ratio);
}

bool IsCross(const Point &a, const Point &b, const Point &c, const Point &d) {
	if (sgn(det(b - a, c - a)) * sgn(det(b - a, d - a)) == 1) return false;
	if (sgn(det(d - c, a - c)) * sgn(det(d - c, b - c)) == 1) return false;
	if (sgn(max(a.x, b.x) - min(c.x, d.x)) < 0) return false;
	if (sgn(max(a.y, b.y) - min(c.y, d.y)) < 0) return false;
	if (sgn(max(c.x, d.x) - min(a.x, b.x)) < 0) return false;
	if (sgn(max(c.y, d.y) - min(a.y, b.y)) < 0) return false;
	return true;
}

Point CalcCross(const Point &a, const Point &b, const Point &c, const Point &d) {
	double mat[2][3];
	mat[0][0] = b.x - a.x, mat[0][1] = c.x - d.x, mat[0][2] = c.x - a.x;
	mat[1][0] = b.y - a.y, mat[1][1] = c.y - d.y, mat[1][2] = c.y - a.y;
	for (int i = 0, j = 0, k; i < 2; ++ i, ++ j) {
		for (k = j; k < 2; ++ k)
			if (sgn(mat[k][i]) != 0) break;
		if (k == 2) continue;
		for (int p = 0; p < 3; ++ p) swap(mat[k][p], mat[j][p]);
		double t = mat[j][i];
		for (int p = 0; p < 3; ++ p) mat[j][p] /= t;
		for (k = 0; k < 2; ++ k)
			if (k != j) {
				t = mat[k][i];
				for (int p = 0; p < 3; ++ p) mat[k][p] -= t * mat[j][p];
			}
	}
	return (a + (b - a) * mat[0][2]);
}

bool Solve() {
	if (!IsCross(p, q, w0, w1)) {
		if (!IsCross(p, q, m0, m1)) return true;
		if (sgn(det(m0 - p, m1 - p)) == 0 && sgn(det(m0 - q, m1 - q)) == 0) return true;
	}
	if (sgn(det(m1 - m0, p - m0)) * sgn(det(m1 - m0, q - m0)) == 1) {
		Point f = CalcFoot(q, m0, m1);
		f = f * 2.0 - q;
		if (IsCross(p, f, m0, m1)) {
			Point c = CalcCross(p, f, m0, m1);
			if (!IsCross(p, c, w0, w1) && !IsCross(c, q, w0, w1)) return true;
		}
	}
	return false;
}

int main() {
	p.scan(), q.scan(), w0.scan(), w1.scan(), m0.scan(), m1.scan();
	puts(Solve() ? "YES" : "NO");
	return 0;
}
