/*
 * $File: kaj.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given N persons with different weights,
 *   and we know a boat can hold at most 2
 *   persons and a boat can not hold things
 *   that weigh more than W, find the minimal
 *   numbers of boats.
 *
 * Solution:
 *   Greedy. Sort the sequence and maintain
 *   two pointers, one from begin to end and
 *   one from end to begin.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 30000;
int w, n, seq[kMaxN];
int res;

int main() {
	scanf("%d%d", &w, &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	sort(seq, seq + n);
	int lb = 0, rb = n - 1;
	while (lb < rb) {
		if (seq[rb] + seq[lb] > w) {
			++ res;
			-- rb;
		}
		else {
			++ res;
			++ lb;
			-- rb;
		}
	}
	if (lb <= rb) ++ res;
	printf("%d\n", res);
	return 0;
}
