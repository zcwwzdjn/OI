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
	double x, y, z;
	Point() {}
	Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
	void scan() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
};

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
	return (Vector(a.x + b.x, a.y + b.y, a.z + b.z));
}

Vector operator - (const Vector &a, const Vector &b) {
	return (Vector(a.x - b.x, a.y - b.y, a.z - b.z));
}

int n;
double rad, ans;
Point start;
Vector dir;

void Check(const Point &core, double r) {
	Vector t = start - core;
	double a = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
	double b = 2.0 * (t.x * dir.x + t.y * dir.y + t.z * dir.z);
	double c = t.x * t.x + t.y * t.y + t.z * t.z - r * r;
	double d = b * b - 4.0 * a * c;
	if (sgn(d) < 0) return;
	d = sqrt(fabs(d));
	double x1 = (-b + d) / (2.0 * a), x2 = (-b - d) / (2.0 * a);
	if (sgn(x1) >= 0) ans = min(ans, x1);
	if (sgn(x2) >= 0) ans = min(ans, x2);
}

int main() {
	start.scan(), dir.scan(), scanf("%lf%d", &rad, &n);
	ans = 1E100;
	for (int i = 0; i < n; ++ i) {
		Point core;
		double r;
		int m;
		core.scan(), scanf("%lf%d", &r, &m);
		Check(core, rad + r);
		for (int j = 0; j < m; ++ j) {
			Vector p;
			p.scan();
			Check(core + p, rad);
		}
	}
	if (ans < 1E90) printf("%.8lf\n", ans);
	else puts("-1");
	return 0;
}
