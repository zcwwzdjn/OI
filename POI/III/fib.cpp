/*
 * $File: fib.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Define F(0) = 'b', F(1) = 'a', and
 *   F(k + 2) = F(k + 1) + F(k). Count how
 *   many times a given string appears in
 *   F(N - 1).
 *
 * Solution:
 *   As the string's length is at most 30,
 *   so we can store for each F(i), the 30 first
 *   chars and 30 last chars. Then dp.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxL = 30, kMaxN = 200;
char pat[kMaxL + 1];
int l, n;

struct Int {
	static const int kMaxD = 64, kN = 1000000000;
	int dig, num[kMaxD];
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
		puts("");
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
			++ c.num[i + 1];
		}
	}
	while (c.num[c.dig]) ++ c.dig;
	return c;
}

Int f[kMaxN];
char pre[kMaxN][kMaxL + 1];
char suf[kMaxN][kMaxL + 1];
char buf[kMaxL * 2 + 1];

int Count(int u, int v) {
	int res = 0;
	int ul = strlen(suf[u]);
	int vl = strlen(pre[v]);
	int buf_idx = 0;
	for (int i = 0; i < ul; ++ i) buf[buf_idx ++] = suf[u][i];
	for (int i = 0; i < vl; ++ i) buf[buf_idx ++] = pre[v][i];
	for (int i = 1; i <= ul; ++ i) {
		int j = l - i;
		if (j >= 1 && j <= vl) {
			int s = ul - i;
			bool chk = true;
			for (int k = 0; k < l; ++ k)
				if (buf[s + k] != pat[k]) {
					chk = false;
					break;
				}
			if (chk) ++ res;
		}
	}
	return res;
}

void Combine(int t, int u, int v) {
	int ul = strlen(pre[u]);
	int vl = strlen(suf[v]);
	if (ul < l) {
		memcpy(pre[t], pre[u], ul);
		int idx = 0;
		while (ul != l && pre[v][idx]) {
			pre[t][ul ++] = pre[v][idx ++];
		}
	}
	else
		memcpy(pre[t], pre[u], l);
	if (vl < l) {
		memcpy(suf[t], suf[v], vl);
		reverse(suf[t], suf[t] + vl);
		int tmp = strlen(suf[u]);
		int idx = tmp - 1;
		while (vl != l && idx >= 0) {
			suf[t][vl ++] = suf[u][idx --];
		}
		reverse(suf[t], suf[t] + vl);
	}
	else
		memcpy(suf[t], suf[v], l);
}

int main() {
	scanf("%s%d", pat, &n);
	l = strlen(pat);
	pre[0][0] = suf[0][0] = 'b';
	pre[1][0] = suf[1][0] = 'a';
	if (l == 1) {
		if (pat[0] == 'b') f[0] = 1;
		else f[1] = 1;
	}
	for (int i = 2; i < n; ++ i) {
		f[i] = f[i - 1] + f[i - 2] + Count(i - 1, i - 2);
		Combine(i, i - 1, i - 2);
	}
	f[n - 1].print();
	return 0;
}
