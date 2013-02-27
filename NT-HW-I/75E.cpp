#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 30;
const int kMaxV = 100;
int n, m;
double d[kMaxV][kMaxV];

inline int sgn(double x) {
	if (fabs(x) < 1E-7) return 0;
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
} st, ed, h[kMaxN], s[kMaxV];

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

double dot(const Vector &a, const Vector &b) {
	return (a.x * b.x + a.y * b.y);
}

double len(const Vector &v) {
	return (sqrt(v.x * v.x + v.y * v.y));
}

bool IsIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
	if (sgn(det(b - a, c - a)) * sgn(det(b - a, d - a)) > 0) return false;
	if (sgn(det(d - c, a - c)) * sgn(det(d - c, b - c)) > 0) return false;
	if (sgn(max(a.x, b.x) - min(c.x, d.x)) < 0) return false;
	if (sgn(max(a.y, b.y) - min(c.y, d.y)) < 0) return false;
	if (sgn(max(c.x, d.x) - min(a.x, b.x)) < 0) return false;
	if (sgn(max(c.y, d.y) - min(a.y, b.y)) < 0) return false;
	return true;
}

bool IsOnOneLine(const Point &a, const Point &b, const Point &c, const Point &d) {
	return (sgn(det(b - a, d - c)) == 0);
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

double CalcDist(const Point &a, const Point &b) {
	double res = len(a - b);
	static Point seq[8];
	bool ban[8];
	memset(ban, false, sizeof(ban));
	int idx = 0;
	for (int i = 0; i < n; ++ i) {
		int j = (i + 1) % n;
		if (IsIntersect(a, b, h[i], h[j])) {
			if (!IsOnOneLine(a, b, h[i], h[j])) {
				seq[idx ++] = CalcIntersect(a, b, h[i], h[j]);
			}
			else return res;
		}
	}
	double add = 0;
	for (int i = 0; i < idx - 1; ++ i)
		for (int j = i + 1; j < idx; ++ j)
			add = max(add, len(seq[i] - seq[j]));
	res += add;
	return res;
}

int main() {
	st.scan(), ed.scan();
	s[m ++] = st;
	s[m ++] = ed;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		h[i].scan();
		s[m ++] = h[i];
	}
	for (int i = 0; i < n; ++ i) {
		int j = (i + 1) % n;
		if (IsIntersect(st, ed, h[i], h[j])) {
			if (!IsOnOneLine(st, ed, h[i], h[j])) {
				s[m ++] = CalcIntersect(st, ed, h[i], h[j]);
			}
		}
	}
	for (int i = 0; i < m; ++ i)
		for (int j = 0; j < m; ++ j)
			d[i][j] = (i == j ? 0 : 1E100);
	for (int i = 0; i < m - 1; ++ i)
		for (int j = i + 1; j < m; ++ j) {
			if (i == 0 || i == 1) {
				if (j > 1 && j < n + 2) continue;
			}
			d[i][j] = CalcDist(s[i], s[j]);
			d[j][i] = d[i][j];
		}
	for (int k = 0; k < m; ++ k)
		for (int i = 0; i < m; ++ i) if (i != k)
			for (int j = 0; j < m; ++ j) if (j != i && j != k)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	printf("%.8lf\n", d[0][1]);
	return 0;
}
