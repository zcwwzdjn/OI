#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

#define mp make_pair

const int kMaxN = 300000, kInf = 0x3f3f3f3f;
int n, p[kMaxN], r[kMaxN];

namespace sgt {
	struct Info {
		int v0, c0, v1, c1;
		Info() {}
		Info(int v0_, int c0_, int v1_, int c1_) {
			v0 = v0_, c0 = c0_, v1 = v1_, c1 = c1_;
		}
	};

	Info operator + (const Info &a, const Info &b) {
		pair<int, int> s[4];
		s[0] = mp(a.v0, a.c0);
		s[1] = mp(a.v1, a.c1);
		s[2] = mp(b.v0, b.c0);
		s[3] = mp(b.v1, b.c1);
		sort(s, s + 4);
		int m = 0;
		for (int i = 0; i < 4; ++ i)
			if (!i || s[i].first != s[i - 1].first) s[m ++] = s[i];
			else s[m - 1].second += s[i].second;
		return Info(s[0].first, s[0].second, s[1].first, s[1].second);
	}

	struct Mark {
		int d;
		Mark() {}
		Mark(int d_) : d(d_) {}
		void clear() {
			d = 0;
		}
	};

	Mark operator * (const Mark &a, const Mark &b) {
		return Mark(a.d + b.d);
	}

	Info operator * (const Info &a, const Mark &b) {
		return Info(a.v0 + b.d, a.c0, a.v1 + b.d, a.c1);
	}

	struct Node {
		Info info;
		Mark mark;
		Node *son[2];
		void update() {
			info = son[0]->info + son[1]->info;
		}
	};

	Node *BuildTree(int l, int r) {
		Node *res = new Node;
		if (l + 1 == r) {
			res->info = Info(0, 1, kInf, 0);
			res->mark = Mark(0);
			res->son[0] = res->son[1] = NULL;
		}
		else {
			int mid = (l + r) >> 1;
			res->son[0] = BuildTree(l, mid);
			res->son[1] = BuildTree(mid, r);
			res->update();
			res->mark.clear();
		}
		return res;
	}

	void DoPush(Node *pos, const Mark &p) {
		if (pos != NULL && p.d) {
			pos->info = pos->info * p;
			pos->mark = pos->mark * p;
		}
	}

	void Push(Node *pos) {
		if (pos != NULL && pos->mark.d) {
			DoPush(pos->son[0], pos->mark);
			DoPush(pos->son[1], pos->mark);
			pos->mark.clear();
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

	int AskOnRange(int l, int r, Node *pos, int pos_l, int pos_r) {
		if (l <= pos_l && r >= pos_r) return ((pos->info.v0 <= 2) * pos->info.c0 + (pos->info.v1 <= 2) * pos->info.c1);
		int mid = (pos_l + pos_r) >> 1;
		return ((l < mid ? AskOnRange(l, r, pos->son[0], pos_l, mid) : 0) + (r > mid ? AskOnRange(l, r, pos->son[1], mid, pos_r) : 0));
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &p[i]);
		r[-- p[i]] = i;
	}
	sgt::Node *root = sgt::BuildTree(0, n);
	long long ans = 0;
	for (int i = n - 1; i >= 0; -- i) {
		int pos = r[i];
		int s[2];
		s[0] = (pos + 1 < n && p[pos + 1] > i ? p[pos + 1] : n);
		s[1] = (pos - 1 >= 0 && p[pos - 1] > i ? p[pos - 1] : n);
		sort(s, s + 2);
		sgt::ChangeOnRange(i, s[0], sgt::Mark(1), root, 0, n);
		if (s[1] < n) sgt::ChangeOnRange(s[1], n, sgt::Mark(-1), root, 0, n);
		ans += sgt::AskOnRange(i, n, root, 0, n) - 1;
	}
	printf("%I64d\n", ans);
	return 0;
}
