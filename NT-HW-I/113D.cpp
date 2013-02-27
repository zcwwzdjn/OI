#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 22, kMaxS = kMaxN * kMaxN;
int n, m, a, b, to[kMaxN][kMaxN + 1], idx[kMaxN][kMaxN], cnt;
double p[kMaxN];
double mat[kMaxS][kMaxS + 1], tmp[kMaxS][kMaxS + 1];
double f[kMaxS][kMaxS];

void Solve(int n, int m) {
	for (int i = 0, j = 0, k; i < n; ++ i, ++ j) {
		for (k = j; k < n; ++ k)
			if (fabs(mat[k][i]) > 1E-10) break;
		if (k == n) continue;
		if (k != j)
			for (int p = 0; p < m; ++ p) swap(mat[j][p], mat[k][p]);
		for (k = j + 1; k < n; ++ k) {
			double t = mat[k][i] / mat[j][i];
			for (int p = j; p < m; ++ p)
				mat[k][p] -= t * mat[j][p];
		}
	}	
	for (int i = n - 1; i >= 0; -- i) {
		mat[i][m - 1] /= mat[i][i];
		for (int j = 0; j < i; ++ j) mat[j][m - 1] -= mat[i][m - 1] * mat[j][i];
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &a, &b);
	-- a, -- b;
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		to[u][++ to[u][0]] = v;
		to[v][++ to[v][0]] = u;
	}
	for (int i = 0; i < n; ++ i) {
		scanf("%lf", &p[i]);
		to[i][++ to[i][0]] = i;
	}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j) idx[i][j] = cnt ++;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			for (int ii = 1; ii <= to[i][0]; ++ ii)
				for (int jj = 1; jj <= to[j][0]; ++ jj) {
					int u = to[i][ii], v = to[j][jj];
					double pi = (u == i ? p[i] : (1.0 - p[i]) / (to[i][0] - 1));
					double pj = (v == j ? p[j] : (1.0 - p[j]) / (to[j][0] - 1));
					f[idx[i][j]][idx[u][v]] += pi * pj;
				}
	for (int i = 0; i < cnt; ++ i)
		if (i / n == i % n) tmp[i][i] = 1.0;
		else
			for (int j = 0; j < cnt; ++ j) {
				tmp[i][j] = f[i][j];
				if (i == j) tmp[i][j] -= 1.0;
			}
	for (int k = 0; k < n; ++ k) {
		memcpy(mat, tmp, sizeof(tmp));
		mat[idx[k][k]][cnt] = 1.0;
		Solve(cnt, cnt + 1);
		if (k) printf(" ");
		printf("%.8lf", mat[idx[a][b]][cnt]);
	}
	printf("\n");
	return 0;
}
