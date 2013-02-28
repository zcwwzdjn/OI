/*
 * $File: kod.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Consider a permutatuon A of N, Bi equals
 *   the number of all Aj such that j < i and
 *   Aj > Ai. Now given B, calculate A.
 *
 * Solution:
 *   Consider backward. We firstly think about
 *   the An. Clearly An is N - Bn, just as the
 *   definition. Then we get a sequence of 
 *   length N - 1, and the set of numbers we can
 *   choose is {1, 2, ..., N} \ {N - Bn}.
 *   So what we should do is to instruct a ds,
 *   and it can return the Kth of a set of integers.
 *   We can do it with segment tree.
 */

#include <cstdio>

const int kMaxN = 30000;
int n, b[kMaxN], a[kMaxN];

struct Node {
	int s;
	Node *son[2];
	void update() {
		s = son[0]->s + son[1]->s;
	}
} node_pool[kMaxN * 2 - 1], *node_idx = node_pool, *root = NULL;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	res->s = r - l;
	if (l + 1 < r) {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
	}
	return res;
}

void ChangeOnPoint(int x, Node *pos, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) {
		pos->s = 0;
		return;
	}
	int mid = (pos_l + pos_r) >> 1;
	if (x < mid)
		ChangeOnPoint(x, pos->son[0], pos_l, mid);
	else
		ChangeOnPoint(x, pos->son[1], mid, pos_r);
	pos->update();
}

int Ask(int k, Node *pos, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) {
		if (k == 1) return pos_l;
		else return -1;
	}
	int mid = (pos_l + pos_r) >> 1;
	if (pos->son[0]->s >= k)
		return Ask(k, pos->son[0], pos_l, mid);
	else
		return Ask(k - pos->son[0]->s, pos->son[1], mid, pos_r);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &b[i]);
	root = BuildTree(0, n);
	for (int i = n - 1; i >= 0; -- i) {
		int k = i + 1 - b[i];
		a[i] = Ask(k, root, 0, n);
		if (a[i] == -1) {
			puts("NIE");
			return 0;
		}
		ChangeOnPoint(a[i], root, 0, n);
	}
	for (int i = 0; i < n; ++ i) printf("%d\n", a[i] + 1);
	return 0;
}
