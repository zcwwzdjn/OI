/*
 * $File: pal.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a string, try to split it into
 *   many even palindromes, and return
 *   answers with minimal and maximal blocks.
 *
 * Solution:
 *   Brute force to check is a substring is a palindrome,
 *   then do a dp.
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 200, kInf = 0x3f3f3f3f;
char buf[kMaxN + 2];
int f[kMaxN + 1], g[kMaxN + 1];
int n;
bool can[kMaxN + 1][kMaxN + 1];

bool Check(int i, int j) {
	while (i < j) {
		if (buf[i] != buf[j]) return false;
		++ i, -- j;
	}
	return true;
}

int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for (int i = 1; i <= n; ++ i) {
		f[i] = kInf;
		g[i] = -kInf;
	}
	for (int i = 1; i <= n; ++ i)
		for (int j = i; j <= n; ++ j)
			can[i][j] = Check(i, j) && ((j - i) & 1);	
	for (int i = 1; i <= n; ++ i)
		for (int j = 0; j < i; ++ j)
			if (can[j + 1][i]) {
				f[i] = min(f[i], f[j] + 1);
				g[i] = max(g[i], g[j] + 1);
			}
	if (f[n] == kInf) puts("NIE");
	else {
		vector<int> sol;
		sol.clear();
		for (int i = n; i != 0; ) {
			sol.push_back(i);
			for (int j = 0; j < i; ++ j)
				if (can[j + 1][i] && f[i] == f[j] + 1) {
					i = j;
					break;
				}
		}
		sol.push_back(0);
		reverse(sol.begin(), sol.end());
		for (int i = 0; i < f[n]; ++ i) {
			if (i) putchar(' ');
			for (int j = sol[i] + 1; j <= sol[i + 1]; ++ j) putchar(buf[j]);
		}
		puts("");
		sol.clear();
		for (int i = n; i != 0; ) {
			sol.push_back(i);
			for (int j = 0; j < i; ++ j)
				if (can[j + 1][i] && g[i] == g[j] + 1) {
					i = j;
					break;
				}
		}
		sol.push_back(0);
		reverse(sol.begin(), sol.end());
		for (int i = 0; i < g[n]; ++ i) {
			if (i) putchar(' ');
			for (int j = sol[i] + 1; j <= sol[i + 1]; ++ j) putchar(buf[j]);
		}
		puts("");
	}
	return 0;
}
