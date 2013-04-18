#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, seq[kMaxN], cnt, begin[kMaxN], end[(kMaxN - 1) * 2], next[(kMaxN - 1) * 2];
int pos[kMaxN], p, lis[kMaxN];
int lb[kMaxN], rb[kMaxN];
int m;
int rec[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

struct Node {
	int cnt;
	Node *son[2];
	void update() {
		cnt = son[0]->cnt + son[1]->cnt;
	}
} node_pool[kMaxN * 2 - 1 + kMaxN * 18], *node_idx = node_pool;

Node *memo[kMaxN + 1], **at = memo + 1;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 < r) {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
	}
	return res;
}

Node *Insert(int x, Node *pos, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) {
		Node *res = node_idx ++;
		res->cnt = pos->cnt + 1;
		return res;
	}
	Node *res = node_idx ++;
	int mid = (pos_l + pos_r) >> 1;
	if (x < mid) {
		res->son[0] = Insert(x, pos->son[0], pos_l, mid);
		res->son[1] = pos->son[1];
	}
	else {
		res->son[0] = pos->son[0];
		res->son[1] = Insert(x, pos->son[1], mid, pos_r);
	}
	return res->update(), res;
}

int Find(int k, Node *l, Node *r, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) return pos_l;
	int mid = (pos_l + pos_r) >> 1;
	if (r->son[0]->cnt - l->son[0]->cnt >= k)
		return Find(k, l->son[0], r->son[0], pos_l, mid);
	else
		return Find(k - (r->son[0]->cnt - l->son[0]->cnt), l->son[1], r->son[1], mid, pos_r);
}


int stack[kMaxN], stop, dcnt;
int start[kMaxN], par[kMaxN];
void Init() {
	for (int i = 0; i < n; ++ i) start[i] = begin[i];
	stack[stop ++] = 0;
	lb[0] = dcnt ++;
	par[0] = -1;
	while (stop) {
		int u = stack[stop - 1];
		bool chk = false;
		for (int &now = start[u], v; now != -1; now = next[now])
			if ((v = end[now]) != par[u]) {
				chk = true;
				stack[stop ++] = v;
				lb[v] = dcnt ++;
				par[v] = u;
				now = next[now];
				break;
			}
		if (!chk) {
			rb[u] = dcnt - 1;
			-- stop;
		}
	}
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &seq[i]);
		pos[i] = seq[i];
	}
	sort(pos, pos + n);
	p = unique(pos, pos + n) - pos;
	for (int i = 0; i < n; ++ i) {
		seq[i] = lower_bound(pos, pos + p, seq[i]) - pos;
		rec[seq[i]] = i;
	}
	at[-1] = BuildTree(0, p);
	for (int u, v, i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	Init();
	for (int i = 0; i < n; ++ i) lis[lb[i]] = i;
	for (int i = 0; i < n; ++ i) at[i] = Insert(seq[lis[i]], at[i - 1], 0, p);
	scanf("%d", &m);
	for (int x, k; m --; ) {
		scanf("%d%d", &x, &k);
		-- x;
		printf("%d\n", rec[Find(k, at[lb[x] - 1], at[rb[x]], 0, p)] + 1);
	}
	return 0;
}
