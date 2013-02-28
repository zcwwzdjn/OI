/*
 * $File: sze.cpp
 * $Author: Wayne <tletletle@163.com?
 *
 * Task:
 *   Given N tasks, the last time of task i
 *   is Ai * T + Bi, where T is the start time.
 *   Find a task todo list to minimize the tot
 *   time.
 *
 * Solution:
 *   Greedy. Task i needs to be done before task
 *   j, iff Aj * Bi < Ai * Bj.
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;
int n, seq[kMaxN];

struct Node {
	double a, b;
} node[kMaxN];

bool Cmp(const int &i, const int &j) {
	return (node[j].a * node[i].b < node[i].a * node[j].b);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		seq[i] = i;
		scanf("%lf%lf", &node[i].a, &node[i].b);
	}
	sort(seq, seq + n, Cmp);
	for (int i = 0; i < n; ++ i) printf("%d\n", seq[i] + 1);
	return 0;
}
