/*
 * $File: sum.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given N and S, find a integer sequence of
 *   length N, sum S, and the difference between
 *   any consecutive numbers is exactly 1.
 *
 * Solution:
 *   Let d[i] be s[i + 1] - s[i]. Then we have
 *       N * (d[1] + d[2] + .. + d[n - 1])
 *     = S + 1 * d[1] + 2 * d[2] + .. + (n - 1) * d[n - 1]
 *   Firstly we let all d be 1. Then we can see if we
 *   change d[i] to -1 what will happen. The sum on left side
 *   will decrease by 2 * N, and the one on right side by 2 * i.
 *   So we have a new problem that given T, use 1 to N - 1 to
 *   make the sum equal to T. We can do this greedily. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;
int n, s, d[kMaxN - 1];

int main() {
	scanf("%d%d", &n, &s);
	if ((n % 4 == 2 || n % 4 == 3) && (abs(s) % 2 != 1)) {
		puts("NIE");
		return 0;
	}
	if ((n % 4 == 0 || n % 4 == 1) && (abs(s) % 2 != 0)) {
		puts("NIE");
		return 0;
	}
	if (abs(s) > n * (n - 1) / 2) {
		puts("NIE");
		return 0;
	}
	int a = n * (n - 1), b = (n - 1) * n / 2 + s;
	if (a < b || (a - b) % 2 != 0) puts("NIE");
	else {
		int c = (a - b) >> 1;
		set<int> s;
		for (int i = 1; i < n; ++ i) s.insert(i);
		for (int i = 0; i < n - 1; ++ i) d[i] = 1;
		while (c) {
			set<int>::iterator it = s.lower_bound(c + 1);
			if (it == s.begin()) break;
			-- it;
			c -= *it;
			d[n - (*it) - 1] = -1;
			s.erase(it);
		}
		if (c) puts("NIE");
		else {
			for (int i = 0, e = 0; i < n; ++ i) {
				printf("%d\n", e);
				if (i + 1 < n) e += d[i];
			}
		}
	}
	return 0;
}
