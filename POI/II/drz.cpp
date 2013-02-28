/*
 * $File: drz.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given depth of each leaf on a complete
 *   binary tree, rebuild the tree.
 *
 * Solution:
 *   Simple search. Just dfs and check.
 */

#include <cstdio>

const int kMaxN = 2500;
int n, seq[kMaxN], idx;

struct Node {
	Node *son[2];
	Node() {
		son[0] = son[1] = NULL;
	}
} *root;

bool fail = false;

void Dfs(Node *cur, int dep) {
	if (dep == seq[idx]) {
		++ idx;
		return;
	}
	if (idx < n && seq[idx] < dep) {
		fail = true;
		return;
	}
	if (idx < n) {
		cur->son[0] = new Node;
		Dfs(cur->son[0], dep + 1);
	}
	if (idx < n) {
		cur->son[1] = new Node;
		Dfs(cur->son[1], dep + 1);
	}
	if (((cur->son[0] == NULL) ^ (cur->son[1] == NULL)) == 1)
		fail = true;
}

void PrintG(Node *cur, int par) {
	printf(" %d", par);
	int rec = ++ idx;
	if (cur->son[0]) PrintG(cur->son[0], rec);
	if (cur->son[1]) PrintG(cur->son[1], rec);
}

void PrintB(Node *cur) {
	putchar('(');
	if (cur->son[0]) PrintB(cur->son[0]);
	if (cur->son[1]) PrintB(cur->son[1]);
	putchar(')');
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	root = new Node;
	Dfs(root, 0);
	if (fail || idx != n) puts("NIE");
	else {
		putchar('0');
		idx = 1;
		if (root->son[0]) PrintG(root->son[0], 1);
		if (root->son[1]) PrintG(root->son[1], 1);
		puts("");
		PrintB(root);
		puts("");
	}
	return 0;
}
