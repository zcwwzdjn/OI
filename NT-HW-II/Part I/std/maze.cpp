#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 100000, kMaxM = 100000;
int n, m;
int ans[kMaxM];

struct Rect {
	int x1, y1, x2, y2;
	Rect() {}
	Rect(int a, int b, int c, int d) : x1(a), y1(b), x2(c), y2(d) {}
};

const int kMaxV = kMaxN, kMaxE = (kMaxN - 1) * 2;
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

Rect rec[kMaxN];
int rec_cnt;

int tmp[kMaxN * 2], tmp_idx, uni[kMaxN * 2], uni_idx, orz[kMaxN * 2], orz_idx;
Rect gen[kMaxN];
int gen_idx;

struct Point {
	int x, y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
} poly[kMaxN], query[kMaxM * 2];

struct Seg {
	Point u, v;
	bool operator < (const Seg &t) const {
		if (u.x != t.u.x) return (u.x < t.u.x);
		return (u.y < t.u.y);
	}
} seg[kMaxN];
int seg_cnt;

int cmd[kMaxM * 2], bel[kMaxM * 2];

bool Cmp(const int &a, const int &b) {
	return (query[a].x != query[b].x ? query[a].x < query[b].x : query[a].y < query[b].y);
}

void Init() {
	int minx = kInf;
	for (int i = 0; i < n; ++ i) minx = min(minx, poly[i].x);
	for (int i = 0; i < n; ++ i) {
		int j = (i + 1 < n ? i + 1 : 0);
		if (poly[i].x == minx && poly[j].x == minx) {
			rotate(poly, poly + i, poly + n);
			break;
		}
	}
	if (poly[0].y > poly[1].y) {
		rotate(poly, poly + 2, poly + n);
		reverse(poly, poly + n);
	}
	seg_cnt = 0;
	for (int i = 0; i < n; ++ i) {
		int j = (i + 1 < n ? i + 1 : 0);
		if (poly[i].x == poly[j].x) {
			seg[seg_cnt].u = poly[i];
			seg[seg_cnt].v = poly[j];
			++ seg_cnt;
		}
	}
	sort(seg, seg + seg_cnt);
	cnt = 0;
	memset(begin, -1, sizeof(begin));
	for (int i = 0; i < m * 2; ++ i) cmd[i] = i;
	sort(cmd, cmd + m * 2, Cmp);
}

typedef pair<int, int> Pair;
typedef set<Pair>::iterator SPIT;
set<Pair> bst, bak;
#define mp make_pair

void Build() {
	rec_cnt = 0;
	bst.clear(), bak.clear();
	int where = 0;
	for (int i = 0, j = 0; i < seg_cnt; i = j) {
		while (j < seg_cnt && seg[i].u.x == seg[j].u.x) ++ j;
		uni_idx = 0;
		orz_idx = 0;
		for (int k = i; k < j; ++ k) {
			if (seg[k].u.y > seg[k].v.y) {
				orz[orz_idx ++] = seg[k].v.y;
				orz[orz_idx ++] = seg[k].u.y;
			}
			else {
				orz[orz_idx ++] = seg[k].u.y;
				orz[orz_idx ++] = seg[k].v.y;
			}
		}
		tmp_idx = 0;
		for (int k = i; k < j; ++ k) {
			int lb = seg[k].u.y, rb = seg[k].v.y;
			if (lb > rb) swap(lb, rb);
			SPIT it = bst.lower_bound(mp(lb, 0));
			if (it != bst.end()) {
				if (it->second >= kInf) -- it;
				while (it != bst.end()) {
					tmp[tmp_idx ++] = it->first;
					SPIT nxt = it;
					if (it->second < kInf) rec[it->second].x2 = seg[i].u.x;
					++ nxt;
					bst.erase(it);
					it = nxt;
					if (it->first > rb && it->second < kInf) break;
				}
			}
		}
		int a = 0, b = 0;
		uni_idx = 0;
		while (a < orz_idx || b < tmp_idx) {
			if (a == orz_idx) uni[uni_idx ++] = tmp[b ++];
			else if (b == tmp_idx || orz[a] < tmp[b]) uni[uni_idx ++] = orz[a ++];
			else uni[uni_idx ++] = tmp[b ++];
		}
		int s = uni_idx;
		tmp_idx = 0;
		for (int k = 0; k < s; ++ k) {
			if (k & 1) {
				if (k + 1 == s || uni[k + 1] != uni[k]) tmp[tmp_idx ++] = uni[k];
			}
			else {
				if (k == 0 || uni[k - 1] != uni[k]) tmp[tmp_idx ++] = uni[k];
			}
		}
		s = tmp_idx;
		gen_idx = 0;
		for (int k = 0; k < s; k += 2) {
			if (tmp[k] != tmp[k + 1]) {
				gen[gen_idx ++] = Rect(seg[i].u.x, tmp[k], j == n ? kInf: seg[j].u.x, tmp[k + 1]);
			}
		}
		s = gen_idx;
		int add = -1;
		for (int l = 0; l < s; ++ l) {
			bool es = false;
			int lb = gen[l].y1, rb = gen[l].y2;
			SPIT it = bak.lower_bound(mp(lb, kInf + kInf));
			if (it != bak.end()) {
				if (it->second >= kInf) -- it;
				while (it != bak.end()) {
					SPIT nxt = it;
					++ nxt;
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
					if (MAX(it->first, gen[l].y1) < MIN(nxt->first, gen[l].y2)) {
						if (!es) {
							es = true;
							++ add;
							rec[rec_cnt + add] = gen[l];
							bst.insert(mp(gen[l].y1, rec_cnt + add));
							bst.insert(mp(gen[l].y2, rec_cnt + add + kInf));
						}
						AddEdge(it->second, rec_cnt + add);
						AddEdge(rec_cnt + add, it->second);
					}
					it = nxt;
					++ it;
					if (it != bak.end() && it->first >= rb) break;
				}
			}
			if (!es) {
				es = true;
				++ add;
				rec[rec_cnt + add] = gen[l];
				bst.insert(mp(gen[l].y1, rec_cnt + add));
				bst.insert(mp(gen[l].y2, rec_cnt + add + kInf));
			}
		}
		for (int k = i; k < j; ++ k) {
			int lb = seg[k].u.y, rb = seg[k].v.y;
			if (lb > rb) swap(lb, rb);
			SPIT it = bak.lower_bound(mp(lb, 0));
			if (it != bak.end()) {
				if (it->second >= kInf) -- it;
				while (it != bak.end()) {
					SPIT nxt = it;
					++ nxt;
					bak.erase(it);
					it = nxt;
					if (it->first > rb && it->second < kInf) break;
				}
			}
		}
		for (int l = 0; l < s; ++ l) {
			bak.insert(mp(gen[l].y1, rec_cnt + l));
			bak.insert(mp(gen[l].y2, rec_cnt + l + kInf));
		}
		rec_cnt += add + 1;
		int nwhere = where, axis = (j == seg_cnt ? kInf : seg[j].u.x);
		while (nwhere < m * 2 && query[cmd[nwhere]].x <= axis) {
			SPIT it = bst.lower_bound(mp(query[cmd[nwhere]].y, 0));
			if (it == bst.end()) break;
			bel[cmd[nwhere]] = (it->second >= kInf ? it->second - kInf : it->second);
			++ nwhere;
		}
		where = nwhere;
	}
}

int dep[kMaxV], anc[17][kMaxV];
int dp[17][kMaxV][2][2];

void Dfs(int u, int p) {
	anc[0][u] = p;
	if (p != -1) {
		dp[0][u][0][0] = abs(rec[u].x1 - rec[p].x1);
		dp[0][u][0][1] = abs(rec[u].x1 - rec[p].x2);
		dp[0][u][1][0] = abs(rec[u].x2 - rec[p].x1);
		dp[0][u][1][1] = abs(rec[u].x2 - rec[p].x2);
	}
	for (int now = begin[u], v; now != -1; now = next[now])
		if ((v = end[now]) != p) {
			dep[v] = dep[u] + 1;
			Dfs(v, u);
		}
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int delta = dep[u] - dep[v];
	for (int j = 16; j >= 0; -- j)
		if (delta >> j & 1) u = anc[j][u];
	for (int j = 16; j >= 0; -- j)
		if (anc[j][u] != anc[j][v]) u = anc[j][u], v = anc[j][v];
	if (u != v) u = anc[0][u];
	return u;
}

int Get(int u, int &ux, int p) {
	if (u == p) return 0;
	int res = 0;
	int q = anc[0][u];
	int b;
	if (rec[u].x1 < rec[q].x1) {
		res += rec[q].x1 - ux;
		ux = rec[q].x1;
		b = 0;
	}
	else {
		res += ux - rec[q].x2;
		ux = rec[q].x2;
		b = 1;
	}
	u = q;
	int delta = dep[u] - dep[p];
	int v[2];
	v[0] = v[1] = kInf;
	v[b] = res;
	for (int j = 16; j >= 0; -- j)
		if (delta >> j & 1) {
			int q = anc[j][u];
			int t[2];
			t[0] = min(v[0] + dp[j][u][0][0], v[1] + dp[j][u][1][0]);
			t[1] = min(v[0] + dp[j][u][0][1], v[1] + dp[j][u][1][1]);
			v[0] = t[0], v[1] = t[1];	
			u = q;
		}
	if (v[0] < v[1]) {
		ux = rec[p].x1;
		res = v[0];
	}
	else {
		ux = rec[p].x2;
		res = v[1];
	}
	return res;
}

int Find(int u, int ux, int v, int vx) {
	int p = Lca(u, v), res = 0;
	res += Get(u, ux, p);
	res += Get(v, vx, p);
	res += abs(ux - vx);
	return res;
}

void Solve() {
	Init(), Build();
	memset(anc, -1, sizeof(anc)), dep[0] = 0, Dfs(0, -1);
	for (int j = 1; j < 17; ++ j)
		for (int i = 0; i < rec_cnt; ++ i)
			if (anc[j - 1][i] != -1) {
				anc[j][i] = anc[j - 1][anc[j - 1][i]];
				for (int a = 0; a < 2; ++ a)
					for (int b = 0; b < 2; ++ b) {
						dp[j][i][a][b] = kInf;
						for (int c = 0; c < 2; ++ c)
							dp[j][i][a][b] = min(dp[j][i][a][b], dp[j - 1][i][a][c] + dp[j - 1][anc[j - 1][i]][c][b]);
					}
			}
	for (int i = 0; i < m; ++ i)
		ans[i] += Find(bel[i << 1], query[i << 1].x, bel[i << 1 | 1], query[i << 1 | 1].x);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &poly[i].x, &poly[i].y);
	scanf("%d", &m);
	for (int i = 0; i < m * 2; ++ i) scanf("%d%d", &query[i].x, &query[i].y);
	Solve();
	for (int i = 0; i < n; ++ i) swap(poly[i].x, poly[i].y);
	for (int i = 0; i < m * 2; ++ i) swap(query[i].x, query[i].y);
	Solve();
	for (int i = 0; i < m; ++ i) printf("%d\n", ans[i]);
	return 0;
}
