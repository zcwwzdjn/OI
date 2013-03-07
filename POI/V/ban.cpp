/*
 * $File: ban.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a integer, transfer it to base
 *   -2 and print the result.
 *
 * Solution:
 *   Simple math.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
int n, seq[kMaxN];

struct Int {
	static const int kN = 1000000000;
	int num[8], dig;
	Int() : dig(0) {
		memset(num, 0, sizeof(num));
	}
	Int(int x) {
		dig = 0;
		memset(num, 0, sizeof(num));
		do {
			num[dig ++] = x % kN;
			x /= kN;
		} while (x);
	}
	void scan() {
		static char buf[32];
		scanf("%s", buf);
		int len = strlen(buf);
		dig = 0;
		reverse(buf, buf + len);
		for (int i = 0; i < len; i += 9) {
			int x = 0;
			for (int j = min(len - 1, i + 8); j >= i; -- j) x = x * 10 + buf[j] - '0';
			num[dig ++] = x;
		}
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
		c.num[i] += a.num[i] + b.num[i];
		if (c.num[i] >= Int::kN) {
			c.num[i] -= Int::kN;
			c.num[i + 1] ++;
		}
	}
	while (c.num[c.dig]) ++ c.dig;
	return c;
}

Int operator / (const Int &a, const int &b) {
	Int c;
	c.dig = a.dig;
	for (int i = c.dig - 1, s = 0; i >= 0; -- i) {
		s = s * Int::kN + a.num[i];
		c.num[i] = s / b;
		s %= b;
	}
	while (c.dig && !c.num[c.dig - 1]) -- c.dig;
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

Int num, one;

void Solve(int sgn, Int num) {
	string res = "";
	while (sgn != 1 || !(num == one)) {
		if (sgn == 1) {
			res += '0' + (num.num[0] & 1);
			num = num / 2;
			sgn = -sgn;
		}
		else {
			res += '0' + (num.num[0] & 1);
			if (num.num[0] & 1) num = num + 1;
			num = num / 2;
			sgn = -sgn;
		}
	}
	res += '1';
	int n = res.size();
	if (n > 100) {
		puts("NIE");
		return;
	}
	for (int i = res.size() - 1, j = 1; i >= 0; -- i)
		if (res[i] == '1') {
			if (j) j = 0;
			else putchar(' ');
			printf("%d", i);
		}
	puts("");
}

int main() {
	one = 1;
	int T;
	for (scanf("%d", &T); T --; ) {
		num.scan();
		Solve(1, num);
		Solve(-1, num);
	}
	return 0;
}
