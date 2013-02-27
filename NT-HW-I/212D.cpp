#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 1000000;
int n, m, s[kMaxN];
int log2[kMaxN + 1], dp[20][kMaxN];
double ans[kMaxN];

int Query(int l, int r) {
	int s = log2[r - l + 1];
	return min(dp[s][l], dp[s][r - (1 << s) + 1]);
}

namespace sgt {
	struct Mark {
		ll v, d;
		Mark() : v(0LL), d(0LL) {}
		Mark(ll v_, ll d_) : v(v_), d(d_) {}
	};

	struct Node {
		int sz;
		Mark mark;
		Node *son[2];
		Node() {
			son[0] = son[1] = NULL;
		}
	} node_pool[kMaxN * 2 - 1], *node_idx = node_pool, *root = NULL;

	Node *BuildTree(int l, int r) {
		Node *res = node_idx ++;
		res->sz = r - l;
		if (l + 1 < r) {
			int mid = (l + r) >> 1;
			res->son[0] = BuildTree(l, mid);
			res->son[1] = BuildTree(mid, r);
		}
		return res;
	}

	void DoPush(Node *pos, const Mark &p) {
		if (pos != NULL && (p.v || p.d)) {
			pos->mark.v += p.v;
			pos->mark.d += p.d;
		}
	}

	void Push(Node *pos) {
		if (pos != NULL && (pos->mark.v || pos->mark.d)) {
			DoPush(pos->son[0], pos->mark);
			DoPush(pos->son[1], Mark(pos->mark.v + pos->mark.d * pos->son[0]->sz, pos->mark.d));
			pos->mark.v = pos->mark.d = 0LL;
		}
	}

	int ChangeOnRange(int l, int r, const Mark &p, Node *pos, int pos_l, int pos_r) {
		if (l <= pos_l && r >= pos_r) {
			DoPush(pos, p);
			return pos->sz;
		}
		Push(pos);
		int mid = (pos_l + pos_r) >> 1;
		int lsz = 0, rsz = 0;
		if (l < mid) lsz = ChangeOnRange(l, r, p, pos->son[0], pos_l, mid);
		if (r > mid) rsz = ChangeOnRange(l, r, Mark(p.v + p.d * lsz, p.d), pos->son[1], mid, pos_r);
		return (lsz + rsz);
	}
	
	ll AskOnPoint(int x, Node *pos, int pos_l, int pos_r) {
		if (pos_l + 1 == pos_r) return pos->mark.v;
		Push(pos);
		int mid = (pos_l + pos_r) >> 1;
		if (x < mid)
			return AskOnPoint(x, pos->son[0], pos_l, mid);
		else
			return AskOnPoint(x, pos->son[1], mid, pos_r);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &s[i]);
		dp[0][i] = s[i];
	}
	log2[1] = 0;
	for (int i = 2; i <= n; ++ i) {
		log2[i] = log2[i - 1];
		if ((i & (i - 1)) == 0) ++ log2[i];
	}
	m = log2[n] + 1;
	for (int j = 1; j < m; ++ j)
		for (int i = 0; i < n; ++ i) {
			dp[j][i] = dp[j - 1][i];
			if (i + (1 << (j - 1)) < n) 
				dp[j][i] = min(dp[j][i], dp[j - 1][i + (1 << (j - 1))]);
		}
	sgt::root = sgt::BuildTree(0, n);
	for (int i = 0; i < n; ++ i) {
		int lb, rb, x, y;
		lb = -1, rb = i;
		while (lb + 1 < rb) {
			int mid = (lb + rb) >> 1;
			if (Query(mid, i - 1) > s[i]) rb = mid;
			else lb = mid;
		}
		x = i - rb;
		lb = i, rb = n;
		while (lb + 1 < rb) {
			int mid = (lb + rb) >> 1;
			if (Query(i + 1, mid) >= s[i]) lb = mid;
			else rb = mid;
		}
		y = lb - i;
		if (x > y) swap(x, y);
		if (x) sgt::ChangeOnRange(0, x, sgt::Mark(s[i], s[i]), sgt::root, 0, n);
		sgt::ChangeOnRange(x, y + 1, sgt::Mark((ll)s[i] * (x + 1), 0LL), sgt::root, 0, n);
		if (x) sgt::ChangeOnRange(y + 1, y + x + 1, sgt::Mark((ll)s[i] * x, -s[i]), sgt::root, 0, n);
	}
	for (int i = 0; i < n; ++ i) {
		ans[i] = sgt::AskOnPoint(i, sgt::root, 0, n);
		ans[i] /= n - i;
	}
	scanf("%d", &m);
	for (int x; m --; ) {
		scanf("%d", &x);
		printf("%.15lf\n", ans[x - 1]);
	}
	return 0;
}
