/*
 * $File: row.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a word equations and each variable
 *   is a 01 string with fixed length, find the
 *   number of solutions.
 *
 * Solution:
 *   Cuz the total length is no more than 10000,
 *   we can have equations for each digit, then
 *   use disjoint set to merge diffrent positions
 *   of different variables, and it means they
 *   have to be equal. Be careful that the answer
 *   may be 0, so we can add 2 new vertices in ds,
 *   one means 0 and another means 1.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxL = 10000;
int n, sz[26], m, idx[26][kMaxL];
char buf[kMaxL + 1];
int s[kMaxL], t[kMaxL];
int ss, tt;

const int kMaxV = kMaxL + 2;

struct DS {
	int root[kMaxV];
	void init(int sz) {
		for (int i = 0; i < sz; ++ i) root[i] = i;
	}
	int find(int x) {
		return (x == root[x] ? x : root[x] = find(root[x]));
	}
} ds;

struct Int {
	int num[4096], dig;
	Int() : dig(0) {
		memset(num, 0, sizeof(num));
	}
	Int(int x) {
		dig = 0;
		memset(num, 0, sizeof(num));
		do {
			num[dig ++] = x % 10;
			x /= 10;
		} while (x);
	}
	void print() {
		for (int i = dig - 1; i >= 0; -- i) printf("%d", num[i]);
		printf("\n");
	}
};

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

int main() {
	int T;
	for (scanf("%d", &T); T --; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) scanf("%d", &sz[i]);
		int tmp = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < sz[i]; ++ j) idx[i][j] = tmp ++;
		scanf("%d%s", &m, buf);
		ss = 0;
		for (int i = 0; i < m; ++ i)
			if (buf[i] == '0') s[ss ++] = tmp;
			else if (buf[i] == '1') s[ss ++] = tmp + 1;
			else for (int j = 0; j < sz[buf[i] - 'a']; ++ j) s[ss ++] = idx[buf[i] - 'a'][j];
		scanf("%d%s", &m, buf);
		tt = 0;
		for (int i = 0; i < m; ++ i)
			if (buf[i] == '0') t[tt ++] = tmp;
			else if (buf[i] == '1') t[tt ++] = tmp + 1;
			else for (int j = 0; j < sz[buf[i] - 'a']; ++ j) t[tt ++] = idx[buf[i] - 'a'][j];
		ds.init(tmp + 2);
		if (ss != tt) puts("0");
		else {
			for (int i = 0; i < ss; ++ i) {
				int u = ds.find(s[i]), v = ds.find(t[i]);
				if (u != v) ds.root[u] = v;
			}
			if (ds.find(tmp) == ds.find(tmp + 1)) puts("0");
			else {
				set<int> s;
				for (int i = 0; i < tmp; ++ i) {
					int j = ds.find(i);
					if (j != ds.find(tmp) && j != ds.find(tmp + 1)) s.insert(j);
				}
				Int res = 1;
				int sz = s.size();
				for (int i = 0; i < sz; ++ i) res = res * 2;
				res.print();
			}
		}
	}
	return 0;
}
