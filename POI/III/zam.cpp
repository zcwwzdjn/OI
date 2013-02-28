/*
 * $File: zam.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a polygon, each edge is parallel to
 *   X-axis or Y-axis. You start from a point in
 *   the polygon, and you're supposed to reach
 *   another point, and you can only walk on the
 *   grid lines, calculate the shortest path.
 *
 * Solution:
 *   Split the polygon to rectangles, and those
 *   rectangles form a tree. Use BST to speed up
 *   the process of scanning and building the tree.
 *   Then do a simple dfs.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxN = 5000, kInf = 0x3f3f3f3f;
int n, ans;

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
} poly[kMaxN], pnt[2];

struct Seg {
	Point u, v;
	bool operator < (const Seg &t) const {
		if (u.x != t.u.x) return (u.x < t.u.x);
		return (u.y < t.u.y);
	}
} seg[kMaxN];
int seg_cnt;

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
}

typedef pair<int, int> Pair;
typedef set<Pair>::iterator SPIT;
set<Pair> bst, bak;
#define mp make_pair

void Build() {
	rec_cnt = 0;
	bst.clear(), bak.clear();
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
	}
}

bool In(const Point &p, const Rect &r) {
	return (p.x >= r.x1 && p.x <= r.x2 && p.y >= r.y1 && p.y <= r.y2);
}

int dep[kMaxV], par[kMaxV];

int Find(int u, int ux, int v, int vx) {
	int res = 0;
	while (u != v) {
		if (dep[u] < dep[v]) swap(u, v), swap(ux, vx);
		int p = par[u];
		if (rec[u].x1 < rec[p].x1) {
			res += rec[p].x1 - ux;
			ux = rec[p].x1;
		}
		else {
			res += ux - rec[p].x2;
			ux = rec[p].x2;
		}
		u = p;
	}
	res += abs(ux - vx);
	return res;
}

void Dfs(int u, int p) {
	par[u] = p;
	for (int now = begin[u], v; now != -1; now = next[now])
		if ((v = end[now]) != p) {
			dep[v] = dep[u] + 1;
			Dfs(v, u);
		}
}

void Calc() {
	int bel[2], s = rec_cnt;
	for (int i = 0; i < 2; ++ i)
		for (int j = 0; j < s; ++ j)
			if (In(pnt[i], rec[j])) {
				bel[i] = j;
				break;
			}
	dep[0] = 0;
	Dfs(0, -1);
	ans += Find(bel[0], pnt[0].x, bel[1], pnt[1].x);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &poly[i].x, &poly[i].y);
	for (int i = 0; i < 2; ++ i) scanf("%d%d", &pnt[i].x, &pnt[i].y);
	Init();
	Build();
	Calc();
	for (int i = 0; i < n; ++ i) swap(poly[i].x, poly[i].y);
	for (int i = 0; i < 2; ++ i) swap(pnt[i].x, pnt[i].y);
	Init();
	Build();
	Calc();
	printf("%d\n", ans);
	return 0;
}
