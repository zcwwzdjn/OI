#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long Hash;
const int kMaxN = 200000, kMaxM = 200000, kSeed = 99991;
int n, m, a[kMaxN + 1], b[kMaxM + 1], p[kMaxM + 1];
Hash mypow[kMaxN + 1];

#undef NULL
#define NULL treap::Node::nil

namespace treap {
	struct Node {
		int key, val, fix, sz;
		Hash hash;
		Node *son[2];
		Node() {
			son[0] = son[1] = NULL;
		}
		static Node nil_ins, *nil;
		void update() {
			sz = son[0]->sz + 1 + son[1]->sz;
			hash = (son[0]->hash * kSeed + val) * mypow[son[1]->sz] + son[1]->hash;
		}
	} *root = NULL, node_pool[kMaxM], *node_idx = node_pool;

	Node Node::nil_ins;
	Node *Node::nil = &nil_ins;

	void Rot(Node **pos, bool t) {
		Node *tptr = (*pos)->son[t];
		(*pos)->son[t] = tptr->son[!t];
		tptr->son[!t] = (*pos);
		(*pos)->update(), tptr->update();
		(*pos) = tptr;
	}

	void Insert(int key, int val, Node **pos = &root) {
		if ((*pos) == NULL) {
			(*pos) = node_idx ++;
			(*pos)->key = key, (*pos)->val = val, (*pos)->fix = rand(), (*pos)->sz = 1, (*pos)->hash = val;
		}
		else {
			bool t = ((*pos)->key < key);
			Insert(key, val, &((*pos)->son[t]));
			if ((*pos)->son[t]->fix > (*pos)->fix)
				Rot(pos, t);
			else
				(*pos)->update();
		}
	}

	void Dispose(Node **pos) {
		if ((*pos)->son[0] == NULL && (*pos)->son[1] == NULL)
			(*pos) = NULL;
		else {
			bool t = ((*pos)->son[0]->fix < (*pos)->son[1]->fix);
			Rot(pos, t);
			Dispose(&((*pos)->son[!t]));
			(*pos)->update();
		}
	}

	void Remove(int key, Node **pos = &root) {
		if ((*pos)->key == key)
			Dispose(pos);
		else {
			bool t = ((*pos)->key < key);
			Remove(key, &((*pos)->son[t]));
			(*pos)->update();
		}
	}
}

int main() {
	NULL->fix = -1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
	for (int i = 1; i <= m; ++ i) {
		scanf("%d", &b[i]);
		p[b[i]] = i;
	}
	mypow[0] = 1ULL;
	for (int i = 1; i <= n; ++ i) mypow[i] = mypow[i - 1] * kSeed;
	for (int i = 1; i <= n; ++ i) treap::Insert(p[i], i);
	Hash hash = 0ULL, delta = 0ULL;
	for (int i = 1; i <= n; ++ i) hash = hash * kSeed + a[i];
	for (int i = 0; i < n; ++ i) delta += mypow[i];
	int ans = (hash == treap::root->hash);
	for (int i = 1; i <= m - n; ++ i) {
		hash += delta;
		treap::Insert(p[n + i], n + i);
		treap::Remove(p[i]);
		ans += (hash == treap::root->hash);
	}
	printf("%d\n", ans);
	return 0;
}
