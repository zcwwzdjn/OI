#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const double kEps = 1E-10;

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
} c, h, s;

double ch, cs, hs;

typedef Point Vector;

Vector operator + (const Vector &a, const Vector &b) {
	return (Vector(a.x + b.x, a.y + b.y));
}

Vector operator - (const Vector &a, const Vector &b) {
	return (Vector(a.x - b.x, a.y - b.y));
}

Vector operator * (const Vector &a, const double &b) {
	return (Vector(a.x * b, a.y * b));
}

double len(const Vector &v) {
	return (sqrt(v.x * v.x + v.y * v.y));
}

double t1, t2;
double ans;

double Solve(double k) {
	Point p = h + (s - h) * k;
	double cp = len(c - p), ph = len(p - h), ps = len(p - s);
	if (sgn(t2 - (cp + ph)) >= 0 && sgn(t1 - (cp + ps + hs)) >= 0) return (cp + min(t2 - (cp + ph), t1 - (cp + ps + hs)));
	double lb = 0.0, rb = 1.0;
	for (int t = 0; t < 300; ++ t) {
		double mid = (lb + rb) * 0.5;
		Point q = c + (p - c) * mid;
		double cq = len(c - q), qh = len(q - h), qs = len(q - s);
		if (sgn(t1 - (cq + qs + hs)) >= 0 && sgn(t2 - (cq + qh)) >= 0) lb = mid;
		else rb = mid;
	}
	return len((p - c) * (lb + rb) * 0.5);
}

int main() {
	scanf("%lf%lf", &t1, &t2);
	c.scan(), h.scan(), s.scan();
	ch = len(c - h), cs = len(c - s), hs = len(h - s);
	t1 += cs + hs;
	t2 += ch;
	if (sgn(t2 - (cs + hs)) >= 0) ans = min(t1, t2);
	else {
		double lb = 0.0, rb = 1.0;
		for (int t = 0; t < 300; ++ t) {
			double lm = lb * 2.0 / 3.0  + rb / 3.0, rm = lb / 3.0 + rb * 2.0 / 3.0;
			if (Solve(lm) < Solve(rm)) lb = lm;
			else rb = rm;
		}
		ans = Solve((lb + rb) * 0.5);
	}
	printf("%.8lf\n", ans);	
	return 0;
}
