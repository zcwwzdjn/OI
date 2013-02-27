#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const double kEps = 1E-6;

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
} p[3];

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

double det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}

bool Solve(const Point &a, const Point &b, const Point &c) {
	Vector x = (a - b) * 0.5, y = (a - c) * 0.5;
	x = Vector(x.y, -x.x), y = Vector(y.y, -y.x);
	double mat[2][3];
	mat[0][0] = x.x, mat[0][1] = y.x, mat[0][2] = ((a - b) * 0.5 + (a - c) * 0.5).x;
	mat[1][0] = x.y, mat[1][1] = y.y, mat[1][2] = ((a - b) * 0.5 + (a - c) * 0.5).y;
	for (int i = 0, j = 0, k; i < 2; ++ i, ++ j) {
		for (k = j; k < 2; ++ k)
			if (sgn(mat[k][i]) != 0) break;
		if (k == 2) continue;
		for (int p = 0; p < 3; ++ p) swap(mat[j][p], mat[k][p]);
		double t = mat[j][i];
		for (int p = 0; p < 3; ++ p) mat[j][p] /= t;
		for (k = 0; k < 2; ++ k) if (k != j) {
			t = mat[k][i];
			for (int p = 0; p < 3; ++ p) mat[k][p] -= t * mat[j][p];
		}
	}
	Point res[4];
   	res[0] = (a + b) * 0.5 + x * mat[0][2];
	res[1] = (a + c) * 0.5 + y * mat[1][2];
	res[2] = c * 2 - res[1];
	res[3] = b * 2 - res[0];
	for (int i = 0; i < 4; ++ i) {
		int j = (i + 1) % 4, k = (j + 1) % 4;
		if (sgn(det(res[j] - res[i], res[k] - res[j])) >= 0) return false;
	}
	puts("YES");
	for (int i = 0; i < 4; ++ i) {
		if (i) printf(" ");
		printf("%.9lf %.9lf", res[i].x, res[i].y);
	}
	return true;
}

int main() {
	int t;
	for (scanf("%d", &t); t --; ) {
		for (int i = 0; i < 3; ++ i) p[i].scan();
		bool fail = true;
		if (sgn(det(p[1] - p[0], p[2] - p[0])) == 0) fail = true;
		else {
			for (int i = 0; i < 3 && fail; ++ i)
				for (int j = 0; j < 3 && fail; ++ j) if (i != j)
					if (Solve(p[i], p[j], p[3 - i - j])) fail = false;
		}
		if (fail) puts("NO");
		puts("");
	}
	return 0;
}
