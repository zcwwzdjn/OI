#include <cmath>
#include <cstdio>
#include <cstring>

const int kMaxN = 400;
int n;
double x[kMaxN], y[kMaxN], z[kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%lf", &x[i]);
	double res = 1E100;
	for (int i = 0; i < n - 1; ++ i)
		for (int j = i + 1; j < n; ++ j) {
			double step = (x[j] - x[i]) / (j - i);
			double sum = 0.0;
			y[0] = x[i] - step * i;
			for (int k = 1; k < n; ++ k) y[k] = y[k - 1] + step;
			for (int k = 0; k < n; ++ k) sum += fabs(x[k] - y[k]);
			if (sum < res) {
				res = sum;
				memcpy(z, y, sizeof(y));
			}
		}
	printf("%.4lf\n", res);
	for (int i = 0; i < n; ++ i) {
		if (i) printf(" ");
		printf("%.10lf", z[i]);
	}
	puts("");
	return 0;
}
