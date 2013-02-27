#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100000, kMaxL = 100000, kMaxM = kMaxN + kMaxL;
int n, o, seq[kMaxM + 1], bel[kMaxM + 1], len[kMaxM + 1], m, alpha;
char buf[kMaxL + 2];
ll ans[kMaxN + 1];

struct Node {
	int v[2], p;
	bool operator == (const Node &t) const {
		return (v[0] == t.v[0] && v[1] == t.v[1]);
	}
} nd[kMaxM + 1], tp[kMaxM + 1];

int cnt[kMaxM + 1], sa[kMaxM + 1], rank[kMaxM + 1], height[kMaxM + 1];
int vis[kMaxN + 1];

void RadixSort(int b) {
	for (int i = 1; i >= 0; -- i) {
		memset(cnt, 0, sizeof(int) * (b + 1));
		for (int j = 1; j <= m; ++ j) ++ cnt[nd[j].v[i]];
		for (int j = 1; j <= b; ++ j) cnt[j] += cnt[j - 1];
		for (int j = m; j >= 1; -- j) tp[cnt[nd[j].v[i]] --] = nd[j];
		memcpy(nd, tp, sizeof(Node) * (m + 1));
	}
	for (int i = 1, j = 1, k = 1; i <= m; i = j, ++ k)
		while (j <= m && nd[i] == nd[j]) rank[nd[j ++].p] = k;
}

struct MonoQueue {
	int q[kMaxM + 1][2], qh, qt;
	MonoQueue() : qh(0), qt(0) {}
	void push(int p, int v) {
		while (qh < qt && v < q[qt - 1][0]) -- qt;
		q[qt][0] = v;
		q[qt ++][1] = p;
	}
	int ask(int p) {
		while (q[qh][1] < p) ++ qh;
		return q[qh][0];
	}
} mq;

namespace sgt {
	struct Node {
		int d;
		Node *son[2];
		Node() {
			son[0] = son[1] = NULL;
		}
	} node_pool[kMaxL * 2 - 1], *node_idx = node_pool, *root = NULL;

	Node *BuildTree(int l, int r) {
		Node *res = node_idx ++;
		if (l + 1 < r) {
			int mid = (l + r) >> 1;
			res->son[0] = BuildTree(l, mid);
			res->son[1] = BuildTree(mid, r);
		}
		return res;
	}

	void DoPush(Node *pos, int d) {
		if (pos != NULL && d)
			pos->d = max(pos->d, d);
	}

	void Push(Node *pos) {
		if (pos != NULL && pos->d) {
			DoPush(pos->son[0], pos->d);
			DoPush(pos->son[1], pos->d);
			pos->d = 0;
		}
	}

	void ChangeOnRange(int l, int r, int d, Node *pos, int pos_l, int pos_r) {
		if (l <= pos_l && r >= pos_r) {
			DoPush(pos, d);
			return;
		}
		Push(pos);
		int mid = (pos_l + pos_r) >> 1;
		if (l < mid) ChangeOnRange(l, r, d, pos->son[0], pos_l, mid);
		if (r > mid) ChangeOnRange(l, r, d, pos->son[1], mid, pos_r);
	}

	int AskOnPoint(int x, Node *pos, int pos_l, int pos_r) {
		if (pos_l + 1 == pos_r) return pos->d;
		Push(pos);
		int mid = (pos_l + pos_r) >> 1;
		if (x < mid)
			return AskOnPoint(x, pos->son[0], pos_l, mid);
		else
			return AskOnPoint(x, pos->son[1], mid, pos_r);
	}
}

int main() {
	scanf("%d%d", &n, &o);
	alpha = 255;
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", buf + 1);
		int s = strlen(buf + 1);
		for (int j = 1; j <= s; ++ j) {
			seq[++ m] = buf[j];
			bel[m] =  i;
			len[m] = s - j + 1;
		}
		seq[++ m] = ++ alpha;
	}
	if (o == 1) {
		for (int i = 1, p = 1; i <= n; ++ i) {
			printf("%I64d", (ll)len[p] * (len[p] + 1) / 2);
			p += len[p] + 1;
			if (i == n) printf("\n");
			else printf(" ");
		}
		return 0;
	}
	for (int i = 1; i <= m; ++ i) {
		nd[i].v[0] = seq[i], nd[i].v[1] = 0;
		nd[i].p = i;
	}
	RadixSort(alpha);
	for (int s = 1; s < m; s <<= 1) {
		for (int i = 1; i <= m; ++ i) {
			nd[i].v[0] = rank[i], nd[i].v[1] = (i + s <= m ? rank[i + s] : 0);
			nd[i].p = i;
		}
		RadixSort(m);
	}
	for (int i = 1; i <= m; ++ i) sa[rank[i]] = i;
	for (int i = 1, j, k = 0; i <= m; height[rank[i ++]] = k)
		for (k ? -- k : 0, j = sa[rank[i] - 1]; seq[i + k] == seq[j + k]; ++ k);
	int b = m - n;
	int l = 1, r = 1, tot = 1;
	vis[bel[sa[1]]] = 1;	
	mq.push(1, height[1]);
	sgt::root = sgt::BuildTree(1, b + 1);
	int last = 0;
	while (true) {
		while (r + 1 <= b && tot < o) {
			++ vis[bel[sa[r + 1]]];
			mq.push(r + 1, height[r + 1]);
			if (vis[bel[sa[r + 1]]] == 1) {
				++ tot;
			}	
			++ r;
			if (last) {
				int v = mq.ask(last + 1);
				sgt::ChangeOnRange(last, r + 1, v, sgt::root, 1, b + 1);
			}
		}
		if (tot >= o) {
			int v = mq.ask(l + 1);
			sgt::ChangeOnRange(l, r + 1, v, sgt::root, 1, b + 1);
			last = l;
			while (true) {
				int delta = (vis[bel[sa[l]]] == 1);
				tot -= delta;
				-- vis[bel[sa[l]]];
				++ l;
				if (tot < o) break;
				last = l;
				int v = mq.ask(l + 1);
				sgt::ChangeOnRange(l, r + 1, v, sgt::root, 1, b + 1);
			}
		}
		if (r == b) break;
	}	
	for (int i = 1; i <= b; ++ i) {
		int v = sgt::AskOnPoint(i, sgt::root, 1, b + 1);
		ans[bel[sa[i]]] += v;
	}
	for (int i = 1; i <= n; ++ i) {
		printf("%I64d", ans[i]);
		if (i == n) printf("\n");
		else printf(" ");
	}
	return 0;
}
