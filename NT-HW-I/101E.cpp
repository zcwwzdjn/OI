#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 20000, kMaxM = 20000, kMaxR = 12000;
int n, m, p, q, x[kMaxN], y[kMaxM];
char sol[kMaxN - 1 + kMaxM - 1 + 1];
unsigned long long rec[kMaxR + 1][kMaxM / 64 + 1];

inline int calc(int a, int b) {
	int c = a + b;
	if (c >= p) c -= p;
	return c;
}

void Solve(int a, int b) {
	static int memo[2][kMaxM + 1];
	int des = 0, src = 1;
	memset(memo[des], 0, sizeof(memo[des]));
	memset(rec, 0, sizeof(rec));
	memo[des][1] = 0;
	for (int j = 2; j <= b; ++ j) memo[des][j] = calc(x[n - 1], y[m - (j - 1)]) + memo[des][j - 1];
	for (int i = 2; i <= a; ++ i) {
		des ^= 1, src ^= 1;
		for (int j = 1; j <= b; ++ j) {
			int t0 = calc(x[n - (i - 1)], y[m - j]) + memo[src][j];
			int t1 = (j == 1 ? -1 : calc(x[n - i], y[m - (j - 1)]) + memo[des][j - 1]);
			if (t0 < t1) { 
				memo[des][j] = t1;
				if (a - i <= kMaxR) rec[a - i][j >> 6] |= (1ULL << (j & 63));
			}
			else 
				memo[des][j] = t0;
		}
	}
	if (a == n && b == m) printf("%d\n", memo[des][m] + calc(x[0], y[0]));
	int ra = a;
	while (a > 1 || b > 1) {
		if (a == 1) {
			sol[q ++] = 'S';
			-- b;
		}
		else if (b == 1) {
			sol[q ++] = 'C';
			-- a;
		}
		else if (ra - a <= kMaxR) {
			if (rec[ra - a][b >> 6] & (1ULL << (b & 63))) {
				sol[q ++] = 'S';
				-- b;
			}
			else {
				sol[q ++] = 'C';
				-- a;
			}
		}
		else {
			Solve(a, b);
			break;
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < n; ++ i) scanf("%d", &x[i]), x[i] %= p;
	for (int j = 0; j < m; ++ j) scanf("%d", &y[j]), y[j] %= p;
	Solve(n, m);
	printf("%s\n", sol);
	return 0;
}
