#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100000, kMaxM = 100000, kOffSet = 100000;
int n, seq[kMaxN], m, cnt, begin[kMaxN], end[kMaxM], next[kMaxM], cost[kMaxM], pos[2 * kOffSet + 1];
ll ans[kMaxM];

void AddEdge(int u, int v, int c) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cost[cnt ++] = c;
}

struct Info {
	ll cv, hv;
	Info() {}
	Info(ll cv_, ll hv_) : cv(cv_), hv(hv_) {}
};

struct Mark {
	ll cd, hd;
	Mark() {}
	Mark(ll cd_, ll hd_) : cd(cd_), hd(hd_) {}
};

Info operator + (const Info &a, const Info &b) {
	return Info(max(a.cv, b.cv), max(a.hv, b.hv));
}

Info operator * (const Info &a, const Mark &b) {
	return Info(a.cv + b.cd, max(a.hv, a.cv + b.hd));
}

Mark operator * (const Mark &a, const Mark &b) {
	return Mark(a.cd + b.cd, max(a.hd, a.cd + b.hd));
}

struct Node {
	Info info;
	Mark mark;
	Node *son[2];
	void update() {
		info = son[0]->info + son[1]->info;
	}
} node_pool[2 * (kMaxN + 1) - 1], *node_idx = node_pool, *root = NULL;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 < r) {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
	}
	return res;
}

void DoPush(Node *pos, const Mark &p) {
	if (p.cd || p.hd) {
		pos->info = pos->info * p;
		pos->mark = pos->mark * p;
	}
}

void Push(Node *pos) {
	if (pos->mark.cd || pos->mark.hd) {
		DoPush(pos->son[0], pos->mark);
		DoPush(pos->son[1], pos->mark);
		pos->mark.cd = pos->mark.hd = 0;
	}
}

void ChangeOnRange(int l, int r, const Mark &p, Node *pos, int pos_l, int pos_r) {
	if (l <= pos_l && r >= pos_r) {
		DoPush(pos, p);
		return;
	}
	Push(pos);
	int mid = (pos_l + pos_r) >> 1;
	if (l < mid) ChangeOnRange(l, r, p, pos->son[0], pos_l, mid);
	if (r > mid) ChangeOnRange(l, r, p, pos->son[1], mid, pos_r);
	pos->update();
}

Info AskOnRange(int l, int r, Node *pos, int pos_l, int pos_r) {
	if (l >= pos_r || r <= pos_l) return Info(0, 0);
	if (l <= pos_l && r >= pos_r) return pos->info;
	Push(pos);
	int mid = (pos_l + pos_r) >> 1;
	return (AskOnRange(l, r, pos->son[0], pos_l, mid) + AskOnRange(l, r, pos->son[1], mid, pos_r));
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	scanf("%d", &m);
	for (int i = 0, l, r; i < m; ++ i) {
		scanf("%d%d", &l, &r);
		-- l, -- r;
		AddEdge(r, l, i);
	}
	memset(pos, -1, sizeof(pos));
	root = BuildTree(0, n + 1);
	for (int i = 0; i < n; ++ i) {
		ChangeOnRange(pos[seq[i] + kOffSet] + 1, i + 1, Mark(seq[i], seq[i]), root, 0, n);
		pos[seq[i] + kOffSet] = i;
		for (int now = begin[i]; now != -1; now = next[now])
			ans[cost[now]] = AskOnRange(end[now], i + 1, root, 0, n).hv;
	}
	for (int i = 0; i < m; ++ i) printf("%lld\n", ans[i]);
	return 0;
}
