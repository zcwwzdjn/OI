/*
 * $File: mal.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given two papers with holes, find the
 *   number of common holes.
 *
 * Solution:
 *   Matrix and math. Actually I don't know
 *   why the algorithm is correct.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
int n, seq[kMaxN];

struct Int {
	int num[64], dig;
	Int() : dig(0) {
		memset(num, 0, sizeof(num));
	}
	Int(long long x) {
		dig = 0;
		memset(num, 0, sizeof(num));
		do {
			num[dig ++] = x % 10;
			x /= 10;
		} while (x);
	}
	void scan() {
		static char buf[64];
		scanf("%s", buf);
		dig = strlen(buf);
		for (int i = 0; i < dig; ++ i) num[dig - i - 1] = buf[i] - '0';
	}
	void print() {
		for (int i = dig - 1; i >= 0; -- i) printf("%d", num[i]);
		printf("\n");
	}
};

Int operator + (const Int &a, const Int &b) {
	Int c;
	c.dig = max(a.dig, b.dig);
	for (int i = 0; i < c.dig; ++ i) {
		c.num[i] += a.num[i] + b.num[i];
		if (c.num[i] >= 10) {
			c.num[i] -= 10;
			c.num[i + 1] ++;
		}
	}
	while (c.num[c.dig]) ++ c.dig;
	return c;
}

Int operator - (const Int &a, const Int &b) {
	Int c = a;
	for (int i = 0; i < c.dig; ++ i) {
		c.num[i] -= b.num[i];
		if (c.num[i] < 0) {
			c.num[i] += 10;
			-- c.num[i + 1];
		}
	}
	while (c.dig > 1 && !c.num[c.dig - 1]) -- c.dig;
	return c;
}

Int operator * (const Int &a, const int &b) {
	Int c;
	c.dig = a.dig;
	for (int i = 0; i < c.dig; ++ i) c.num[i] = a.num[i] * b;
	for (int i = 0; i < c.dig; ++ i) {
		c.num[i + 1] += c.num[i] / 10;
		c.num[i] %= 10;
	}
	while (c.num[c.dig]) {
		c.num[c.dig + 1] += c.num[c.dig] / 10;
		c.num[c.dig] %= 10;
		++ c.dig;
	}
	return c;
}

int cmp(const Int &a, const Int &b) {
	if (a.dig < b.dig) return -1;
	if (a.dig > b.dig) return 1;
	for (int i = a.dig - 1; i >= 0; -- i) {
		if (a.num[i] < b.num[i]) return -1;
		if (a.num[i] > b.num[i]) return 1;
	}
	return 0;
}

bool operator < (const Int &a, const Int &b) {
	return (cmp(a, b) == -1);
}

bool operator > (const Int &a, const Int &b) {
	return (cmp(a, b) == 1);
}

bool operator == (const Int &a, const Int &b) {
	return (cmp(a, b) == 0);
}

const int kBelong[2][2] = {
	{2, 3},
	{1, 0}
};
Int x, y;
Int pow2[kMaxN];
Int mat[2][4];

const int kMatrix[4][4][4] = {
	{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 3, 1},
		{0, 0, 0, 1}
	},
	{
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 0, 1, 3}
	},
	{
		{3, 1, 1, 1},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	},
	{
		{1, 0, 0, 1},
		{1, 3, 1, 0},
		{0, 0, 1, 1},
		{0, 0, 0, 0}
	}
};

int main() {
	scanf("%d", &n);
	x.scan(), y.scan();
	pow2[0] = 1;
	for (int i = 1; i < n; ++ i) pow2[i] = pow2[i - 1] * 2;
	for (int i = 0; i < n; ++ i) {
		int a = !(x < pow2[n - i - 1]), b = !(y < pow2[n - i - 1]);
		seq[i] = kBelong[a][b];
		if (a) x = x - pow2[n - i - 1];
		if (b) y = y - pow2[n - i - 1];
	}
	int des = 0, src = 1;
	mat[0][0] = 1, mat[0][1] = 0, mat[0][2] = 0, mat[0][3] = 0;
	for (int i = 0; i < n; ++ i) {
		des ^= 1, src ^= 1;
		for (int j = 0; j < 4; ++ j) mat[des][j] = 0;
		for (int j = 0; j < 4; ++ j)
			for (int k = 0; k < 4; ++ k)
				mat[des][k] = mat[des][k] + mat[src][j] * kMatrix[seq[i]][j][k];
	}
	mat[des][0].print();
	return 0;
}
