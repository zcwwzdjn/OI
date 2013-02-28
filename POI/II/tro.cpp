/*
 * $File: tro.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a finite sequence of positive integers,
 *   find three to construct a triangle.
 *
 * Solution:
 *   Easy to prove that if all integers are not
 *   greater than a billion, we just need to save
 *   45 numbers according to the fibonacci.
 *   Then just brute force.
 */

#include <cstdio>
#include <algorithm>

using std::sort;

int n, seq[45];

int main() {
	while (n < 45 && scanf("%d", &seq[n]) != EOF && seq[n] != 0) ++ n;
	sort(seq, seq + n);
	for (int i = 0; i < n - 2; ++ i)
		for (int j = i + 1; j < n - 1; ++ j)
			for (int k = j + 1; k < n; ++ k)
				if (seq[i] + seq[j] > seq[k]) {
					printf("%d %d %d\n", seq[i], seq[j], seq[k]);
					return 0;
				}
	puts("NIE");
	return 0;
}
