#include <cmath>
#include <cstdio>

const double kEps = 1E-7, kPi = acos(-1.0);
double a, b, l, w;

inline int sgn(double x) {
	if (fabs(x) < kEps) return 0;
	if (x > 0.0) return 1;
	return -1;
}

double Calc(double x) {
	return ((l * cos(x) + w / sin(x) - a) * tan(x));
}

bool Check(double lim) {
	w = lim;
	double lb = 0.0, rb = kPi * 0.5;
	for (int t = 0; t < 100; ++ t) {
		double lm = lb + (rb - lb) / 3.0, rm = rb - (rb - lb) / 3.0;
		if (Calc(lm) < Calc(rm)) lb = lm;
		else rb = rm;
	}
	double t = Calc((lb + rb) * 0.5);
	if (sgn(t - b) < 0) return true;
	return false;
}

int main() {
	scanf("%lf%lf%lf", &a, &b, &l);
	if (a > b) a += b, b = a - b, a = a - b;
	if (sgn(l - b) <= 0) {
		printf("%.8lf\n", (a < l ? a : l));
		return 0;
	}
	double lb = 0.0, rb = l;
	for (int t = 0; t < 100; ++ t) {
		double mid = (lb + rb) * 0.5;
		if (Check(mid)) lb = mid;
		else rb = mid;
	}
	if (sgn(lb) != 0) printf("%.8lf\n", lb);
	else puts("My poor head =(");
	return 0;
}
