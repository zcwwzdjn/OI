/*
 * $File: ukl.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some rules like Afba which means
 *   a should be f A b where A is an operator,
 *   find minimal number of gates needed.
 *
 * Solution:
 *   Firstly find out for each result what
 *   kind of kind are needed, then do recursion.
 *   Strange problem.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
int n, m, rec[26];
char buf[8];

struct Node {
	char op;
	int a, b;
	Node() {}
	Node(char op_, int a_, int b_) : op(op_), a(a_), b(b_) {}
} node[kMaxN];

bool vis[kMaxN];

int Find(char op, int a, int b) {
	int res = 0;
	while (res < m) {
		if (op == node[res].op && a == node[res].a && b == node[res].b) break;
		++ res;
	}
	return res;
}

int Dfs(int u) {
	if (u < 0 || vis[u]) return 0;
	vis[u] = true;
	return (1 + Dfs(node[u].a) + Dfs(node[u].b));
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < 26; ++ i) rec[i] = -i - 1;
	for (int i = 0; i < n; ++ i) {
		scanf("%s", buf);
		int s = Find(buf[0], rec[buf[1] - 'a'], rec[buf[2] - 'a']);
		if (s == m) node[m ++] = Node(buf[0], rec[buf[1] - 'a'], rec[buf[2] - 'a']);
		rec[buf[3] - 'a'] = s;
	}
	int res = 0;
	for (int i = 0; i < 26; ++ i) res += Dfs(rec[i]);
	printf("%d\n", res);
	return 0;
}
