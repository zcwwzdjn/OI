#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMod = 1000000007;
int l, r, inv;

int PowerMod(int a, int b) {
	int res = 1, tmp = a;
	while (b) {
		if (b & 1) res = (long long)res * tmp % kMod;
		b >>= 1;
		tmp = (long long)tmp * tmp % kMod;
	}
	return res;
}

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

struct Matrix {
	int v[9][9];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	Matrix() {
		memset(v, 0, sizeof(v));
	}
} e, f, a;

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix c;
	for (int i = 0; i < 9; ++ i)
		for (int j = 0; j < 9; ++ j)
			for (int k = 0; k < 9; ++ k)
				UPT(c.v[i][j], (long long)a.v[i][k] * b.v[k][j] % kMod);
	return c;
}

Matrix PowerMod(const Matrix &a, int b) {
	Matrix res = e, tmp = a;
	while (b) {
		if (b & 1) res = res * tmp;
		b >>= 1;
		tmp = tmp * tmp;
	}
	return res;
}

int Solve(int n) {
	if (n == 0) return 0;
	a.clear();
	for (int i = 0; i < 8; ++ i) a.v[i][0] = 1;
	a.v[8][0] = 4;
	a = PowerMod(f, n - 1) * a;
	int res = a.v[8][0];
	if (n >= 3) {
		a.clear();
		for (int i = 0; i < 8; ++ i) a.v[i][0] = 1;
		a.v[8][0] = 0;
		a = PowerMod(f, (n - 1) / 2) * a;
		res += a.v[8][0];
	}
	res += 4;
	return ((long long)res * inv % kMod);
}

int main() {
	inv = PowerMod(2, kMod - 2);
	for (int i = 0; i < 9; ++ i) e.v[i][i] = 1;
	f.v[0][2] = f.v[0][4] = f.v[1][2] = f.v[1][4] = 1;
	f.v[2][0] = f.v[2][6] = f.v[3][0] = f.v[3][6] = 1;
	f.v[4][1] = f.v[4][7] = f.v[5][1] = f.v[5][7] = 1;
	f.v[6][3] = f.v[6][5] = f.v[7][3] = f.v[7][5] = 1;
	f.v[0][4] = 0, f.v[1][2] = 0;
	for (int i = 0; i < 9; ++ i) f.v[8][i] = 1;
	scanf("%d%d", &l, &r);
	int res = Solve(r) - Solve(l - 1);
	if (res < 0) res += kMod;
	printf("%d\n", res);
	return 0;
}
