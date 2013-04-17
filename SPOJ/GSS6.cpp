#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kInf = 0x3f3f3f3f;
int n, m, seq[kMaxN];

struct Info {
	int s, v, lv, rv;
	Info() {}
	Info(int s_, int v_, int lv_, int rv_) : s(s_), v(v_), lv(lv_), rv(rv_) {}
};

Info operator + (const Info &a, const Info &b) {
	return Info(a.s + b.s, max(a.rv + b.lv, max(a.v, b.v)), max(a.lv, a.s + b.lv), max(b.rv, b.s + a.rv));
}

#undef NULL
#define NULL Node::nil

struct Node {
	Info org, acc;
	int sz;
	Node *son[2], *par;
	Node() { son[0] = son[1] = par = NULL; }
	static Node nil_ins, *nil;
	void update() {
		acc = son[0]->acc + org + son[1]->acc;
		sz = son[0]->sz + 1 + son[1]->sz;
	}
} node_pool[kMaxN * 2 + 2], *node_idx = node_pool, *root = NULL;

Node Node::nil_ins;
Node *Node::nil = &nil_ins;

Node *NodeAlloc(int v, Node *npar) {
	Node *res = node_idx ++;
	res->org = res->acc = Info(v, v, v, v), res->sz = 1;
	res->par = npar;
	return res;
}

void Rot(Node *pos, bool t) {
	Node *tptr = pos->son[t], *tmp = NULL;
	pos->son[t] = tptr->son[!t];
	if ((tmp = tptr->son[!t]) != NULL) tmp->par = pos;
	tptr->son[!t] = pos;
	if ((tmp = pos->par) != NULL) tmp->son[tmp->son[1] == pos] = tptr;
	else root = tptr;
	pos->par = tptr;
	tptr->par = tmp;
}

void Splay(Node *pos, Node * &des = root) {
	Node *ngra, *npar;
	bool d1, d2;
	while (pos != des && (npar = pos->par) != des) {
		ngra = npar->par;
		if ((d1 = (ngra->son[1] == npar)) == (d2 = (npar->son[1] == pos)))
			Rot(ngra, d1), Rot(npar, d2);
		else
			Rot(npar, d2), Rot(ngra, d1);
		ngra->update(), npar->update();
	}
	if (pos != des) Rot(npar = des, des->son[1] == pos), npar->update();
	pos->update();
}

void Kth(int k, Node * &des) {
	Node *pos = des;
	int dk;
	while ((dk = k - pos->son[0]->sz - 1)) {
		pos = pos->son[dk > 0];
		if (dk > 0) k = dk;
	}
	Splay(pos, des);
}

Node *BuildTree(int l, int r, Node *npar) {
	if (l > r) return NULL;
	int mid = (l + r) >> 1;
	Node *res = NodeAlloc(seq[mid], npar);
	res->son[0] = BuildTree(l, mid - 1, res);
	res->son[1] = BuildTree(mid + 1, r, res);
	res->update();
	return res;
}

void Select(int l, int r) {
	++ l, ++ r;
	Kth(r + 1, root);
	Kth(l - 1, root->son[0]);
}

int main() {
	NULL->acc = NULL->org = Info(0, -kInf, -kInf, -kInf);
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	root = NodeAlloc(0, root);
	root->son[0] = NodeAlloc(0, root);
	root->son[0]->son[1] = BuildTree(0, n - 1, root->son[0]);
	root->son[0]->update();
	root->update();
	scanf("%d", &m);
	while (m --) {
		static char cmd[2];
		static int x, y;
		scanf("%s", cmd);
		if (cmd[0] == 'I') {
			scanf("%d%d", &x, &y);
			Select(x, x - 1);
			root->son[0]->son[1] = NodeAlloc(y, root->son[0]);
			root->son[0]->update();
			root->update();
		}
		else if (cmd[0] == 'D') {
			scanf("%d", &x);
			Select(x, x);
			root->son[0]->son[1] = NULL;
			root->son[0]->update();
			root->update();
		}
		else if (cmd[0] == 'R') {
			scanf("%d%d", &x, &y);
			Select(x, x);
			root->son[0]->son[1]->org = root->son[0]->son[1]->acc = Info(y, y, y, y);
			root->son[0]->update();
			root->update();
		}
		else {
			scanf("%d%d", &x, &y);
			if (x > y) swap(x, y);
			Select(x, y);
			printf("%d\n", root->son[0]->son[1]->acc.v);
		}
	}
	return 0;
}
