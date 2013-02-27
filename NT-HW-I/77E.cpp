#include <cmath>
#include <cstdio>

int main() {
	int t, k;
	double R, r;
   	for (scanf("%d", &t); t --; ) {
		scanf("%lf%lf%d", &R, &r, &k);
		double lb = 1.0 / (2.0 * R);
		double rb = 1.0 / (2.0 * r);
		double h = k * (rb - lb);
		double t = (rb - lb) * 0.5;
		double x = lb + t, y = h;
		double d = sqrt(x * x + y * y);
		printf("%.8lf\n", 0.5 * (1.0 / (d - t) - 1.0 / (d + t)));
	}	
	return 0;
}
