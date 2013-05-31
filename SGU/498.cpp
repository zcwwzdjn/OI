#include <cstdio>

// let p <= 1.0 - original_p
// let q <= 1.0 - original_q
// ans = \int_0^1{f(p) dp \int_0^p{g(q) dq}}
// f(p) * C(n1, m1) * \int_0^1{p^{n1-m1} (1-p)^m1 dp} = C(n1, m1) * {p^{n1-m1} (1-p)^m1}
// g(q) * C(n2, m2) * \int_0^1{q^{n2-m2} (1-q)^m2 dq} = C(n2, m2) * {q^{n2-m2} (1-q)^m2}
// use formula: \int{udv} = uv - \int{vdu}

double sum[2222][111]; // sum[n][m] => \int_0^1{p^{n-m} (1-p)^m dp}
double coef[1111][55][55]; // coef[n][m][i] => the coef of {p^{n-i+1} (1-p)^i} in \int_0^p{q^{n-m} (1-q)^m dq}

int main() {
	for (int n = 0; n < 2222; ++ n) {
		sum[n][0] = 1.0 / (n + 1);
		for (int m = 1; m < 111; ++ m) {
			if (m > n) break;
			sum[n][m] = m * 1.0 / (n - m + 1) * sum[n][m - 1];	
		}
	}
	for (int n = 0; n < 1111; ++ n)
		for (int m = 0; m < 55; ++ m) {
			if (m > n) break;
			coef[n][m][m] = 1.0 / (n - m + 1);
			for (int i = m - 1; i >= 0; -- i)
				coef[n][m][i] = m * 1.0 / (n - m + 1) * coef[n][m - 1][i];
		}
	int n1, m1, n2, m2;
	int T;
	for (scanf("%d", &T); T --; ) {
		scanf("%d%d%d%d", &n1, &m1, &n2, &m2);
		double res = 0.0;
		for (int i = m2; i >= 0; -- i) {
			int n = n1 + n2 + 1;
			int m = m1 + i;
			res += coef[n2][m2][i] * sum[n][m];
		}
		res /= sum[n1][m1] * sum[n2][m2];
		printf("%.10lf\n", res);
	}
	return 0;
}
