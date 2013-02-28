/*
 * $File: add.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some numbers in increasing order,
 *   find the maximal H, that you can choose
 *   a set of numbers, satisfied that if you
 *   use numbers belong to the set, and when
 *   the sum is not greater than H, the sum
 *   must appear in the original sequence.
 *
 * Solution:
 *   First of all the first number must be choose.
 *   Then suppose we choose a set that we can
 *   get the first K numbers. If we can get a number
 *   greater than seq[K] less than seq[K + 1], we
 *   can't choose seq[K + 1] so the answer is seq[K].
 *   Otherwise the maximal H is not less than seq[K + 1],
 *   so we just simply do same from K + 1.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kMaxR = 10000;
int n, h[kMaxN], m, s[kMaxN];
bool vis[kMaxR + 1];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &h[i]);
	vis[s[m ++] = h[0]] = true;
	for (int i = 1; i < n; ++ i) {
		bool chk = true;
		for (int j = h[i - 1] + 1; j < h[i] && chk; ++ j)
			for (int k = 0; k < m && chk; ++ k)
				if (vis[j - s[k]]) chk = false;
		if (!chk) {
			printf("%d\n", h[i - 1]);
			for (int k = 0; k < m; ++ k) printf("%d\n", s[k]);
			return 0;
		}
		chk = false;
		for (int k = 0; k < m && !chk; ++ k)
			if (vis[h[i] - s[k]]) chk = true;
		vis[h[i]] = true;
		if (!chk) s[m ++] = h[i];
	}
	printf("%d\n", h[n - 1]);
	for (int k = 0; k < m; ++ k) printf("%d\n", s[k]);
	return 0;
}
