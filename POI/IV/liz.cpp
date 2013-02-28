/*
 * $File: liz.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   A set X of natural number is n-k-special
 *   if for every x in X we have 1 <= x <= n and
 *   the sum of all numbers is greater than k and
 *   X does not contain a pair of consecutive
 *   numbers. Given n and k, find the number of
 *   n-k-special sets.
 *
 * Solution:
 *   Dynamic programming. Firstly ignore the second
 *   condition and count a answer, then count the
 *   answer when the sum is not greater than k, and
 *   so the program runs faster.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct Int {
	static const int kN = 1000000000;
	int dig, num[4];
	Int() : dig(0) {
		memset(num, 0, sizeof(num));
	}
	Int(int x) {
		memset(num, 0, sizeof(num));
		num[(dig = 1) - 1] = x;
	}
	void print() {
		printf("%d", num[dig - 1]);
		for (int i = dig - 2; i >= 0; -- i) printf("%09d", num[i]);
		printf("\n");
	}
};

Int operator + (const Int &a, const Int &b) {
	Int c;
	c.dig = max(a.dig, b.dig);
	for (int i = 0; i < c.dig; ++ i) {
		int &t = c.num[i];
		t += a.num[i] + b.num[i];
		if (t >= Int::kN) {
			t -= Int::kN;
			c.num[i + 1] ++;
		}
	}
	while (c.num[c.dig]) ++ c.dig;
	return c;
}

Int operator - (const Int &a, const Int &b) {
	Int c;
	c.dig = a.dig;
	for (int i = 0; i < c.dig; ++ i) {
		int &t = c.num[i];
		t += a.num[i] - b.num[i];
		if (t < 0) {
			t += Int::kN;
			c.num[i + 1] --;
		}
	}
	while (c.dig > 1 && !c.num[c.dig - 1]) -- c.dig;
	return c;
}

const int kMaxN = 100, kMaxK = 400;
int n, k;
Int f[kMaxN][2], g[kMaxN][2][kMaxK + 1];

int main() {
	scanf("%d%d", &n, &k);
	f[0][0] = f[0][1] = 1;
	for (int i = 1; i < n; ++ i) {
		f[i][0] = f[i - 1][0] + f[i - 1][1];
		f[i][1] = f[i - 1][0];
	}
	g[0][0][0] = g[0][1][1] = 1;
	int s = min(k, 1);
	for (int i = 1; i < n; ++ i) {
		for (int j = 0; j <= s; ++ j) {
			g[i][0][j] = g[i - 1][0][j] + g[i - 1][1][j];
			if (j + i + 1 <= k) g[i][1][j + i + 1] = g[i - 1][0][j];
		}
		s = min(k, s + i + 1);
	}
	Int res = f[n - 1][0] + f[n - 1][1];
	for (int j = 0; j <= s; ++ j) res = res - (g[n - 1][0][j] + g[n - 1][1][j]);
	res.print();
	return 0;
}
