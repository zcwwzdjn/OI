/*
 * $File: rez.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some intervals, find the maximal
 *   sum of length of the intervals you choose
 *   and make no 2 intervals intersect.
 *
 * Solution:
 *   Dynamic programming. First sort the intervals
 *   by the value of end point, then let DP[i] be
 *   the answer when choose the ith interval as
 *   the last one. When we consider DP[i], and the
 *   start point of ith interval is T, then we can
 *   choose all j that Right[j] <= T. As we sort
 *   the sequence before, it's easy to calculate
 *   DP[i].
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;
int n, dp[kMaxN], rec[kMaxN];

struct Node {
	int a, b;
	Node() {}
	Node(int a_, int b_) : a(a_), b(b_) {}
	bool operator < (const Node &t) const {
		if (b != t.b) return (b < t.b);
		return (a < t.a);
	}
} seq[kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &seq[i].a, &seq[i].b);
	sort(seq, seq + n);
	int res = 0;
	for (int i = 0; i < n; ++ i) {
		dp[i] = seq[i].b - seq[i].a;
		int j = lower_bound(seq, seq + n, Node(0, seq[i].a + 1)) - seq;
		-- j;
		if (j >= 0) dp[i] += rec[j];
		res = max(res, dp[i]);
		rec[i] = dp[i];
		if (i) rec[i] = max(rec[i], rec[i - 1]);
	}
	printf("%d\n", res);
	return 0;
}
