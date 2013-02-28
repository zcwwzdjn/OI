/*
 * $File: poc.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a sequence of numbers of 0, 1, 2,
 *   in each turn you can move 3 consecutive
 *   numbers to the end of the sequence.
 *   Find a solution, to make the whole sequence
 *   non-decreasing. Assume the number of 2
 *   is at least 3.
 *
 * Solution:
 *   Notice that if we move (N - 3, N - 1) repeatly,
 *   the last 4 numbers rotate. So if we want move
 *   number j to number i, we can move j to the last
 *   4, and rotate until (j - i) % 3 == 0. Then move
 *   the numbers between i and j backward.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 2000;
int n, seq[kMaxN], tmp[kMaxN];
int cnt[3];

void MoveBack(int l, int r) {
	int sz = r - l + 1;
	for (int i = 0; i < sz; ++ i) tmp[i] = seq[l + i];
	for (int i = r + 1; i < n; ++ i) seq[i - r - 1 + l] = seq[i];
	for (int i = 0; i < sz; ++ i) seq[n - (sz - i - 1) - 1] = tmp[i];
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static char buf[2];
		scanf("%s", buf);
		if (buf[0] == 'c') seq[i] = 0;
		else if (buf[0] == 'n') seq[i] = 1;
		else seq[i] = 2;
	}
	for (int i = 0; i < n; ++ i) ++ cnt[seq[i]];
	for (int i = 0; i < cnt[0] + cnt[1]; ++ i) {
		int tar = (i >= cnt[0]);
		int j = i;
		while (tar != seq[j]) ++ j;
		if ((j - i) % 3 == 0) {
			for (int k = 0; k < (j - i) / 3; ++ k) {
				printf("%d\n", i + 1);
			}
			MoveBack(i, j - 1);
		}
		else {
			if (j < n - 4) {
				printf("%d\n", j + 1);
				MoveBack(j, j + 2);
				j = n - 3;
			}
			while ((j - i) % 3 != 0) {
				printf("%d\n", n - 3);
				MoveBack(n - 4, n - 2);
				j = (j - (n - 4) + 1) % 4 + (n - 4);
			}
			for (int k = 0; k < (j - i) / 3; ++ k) {
				printf("%d\n", i + 1);
			}
			MoveBack(i, j - 1);
		}
	}
	return 0;
}
