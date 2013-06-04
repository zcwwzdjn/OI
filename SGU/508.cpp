#include <cstdio>

long long c[55][55];
int n, l1, l2, p;

int main() {
	for (int i = 0; i < 55; ++ i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++ j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d%d%d%d", &n, &l1, &l2, &p);
	for (int l = 0; l <= n; ++ l)
		for (int a = 0; a <= n - l; ++ a) {
			int b = a + l;
			long long _1 = 0, _2 = 0;
			for (int k = a; k <= b; ++ k)
				_1 += c[k][l1] * c[n - k][l2];
			for (int k = 0; k <= n; ++ k)
				_2 += c[k][l1] * c[n - k][l2];
			if (_1 * 100 >= _2 * p) {
				printf("%d %d\n", a, b);
				return 0;
			}
		}
	return 0;
}
