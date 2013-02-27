#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxK = 50;
int k, c[kMaxK];
long long p;
vector<long long> fact;

struct Matrix {
	int v[kMaxK][kMaxK];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	Matrix() {
		clear();
	}
} e, f, a, b;

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix c;
	for (int i = 0; i < k; ++ i)
		for (int j = 0; j < k; ++ j)
			for (int l = 0; l < k; ++ l)
				c.v[i][j] = (c.v[i][j] + a.v[i][l] * b.v[l][j]) % 2;
	return c;
}

Matrix PowerMod(const Matrix &a, long long b) {
	Matrix res = e, tmp = a;
	while (b) {
		if (b & 1) res = res * tmp;
		b >>= 1;
		tmp = tmp * tmp;
	}
	return res;
}

bool Check() {
	f.clear();
	for (int i = 0; i < k - 1; ++ i) f.v[i][i + 1] = 1;
	for (int i = 0; i < k; ++ i) f.v[k - 1][i] = c[k - 1 - i];
	b = PowerMod(f, p) * a;
	for (int i = 0; i < k; ++ i)
		if (a.v[i][0] != b.v[i][0]) return false;
	int sz = fact.size();
	for (int i = 0; i < sz; ++ i) {
		long long q = fact[i];
		b = PowerMod(f, q) * a;
		bool fail = false;
		for (int i = 0; i < k; ++ i)
			if (a.v[i][0] != b.v[i][0]) {
				fail = true;
				break;
			}
		if (!fail) return false;
	}
	return true;
}

int main() {
	scanf("%d", &k);
	for (int i = 0; i < k; ++ i) e.v[i][i] = 1;
	p = (1LL << k) - 1;
	long long tmp = p;
	for (long long q = 2; q * q <= tmp; ++ q)
		if (tmp % q == 0) {
			fact.push_back(p / q);
			while (tmp % q == 0) tmp /= q;
		}
	if (tmp != 1) fact.push_back(p / tmp);
	for (a.v[k - 1][0] = 1; ; ) {
		for (int i = 0; i < k; ++ i) c[i] = rand() % 2;
		if (Check()) break;
	}
	for (int i = 0; i < k; ++ i) {
		if (i) printf(" ");
		printf("%d", c[i]);
	}
	printf("\n");
	for (int i = 0; i < k; ++ i) {
		if (i) printf(" ");
		printf("%d", a.v[i][0]);
	}
	printf("\n");
	return 0;
}
