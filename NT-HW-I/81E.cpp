#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
	int a, b;
	Pair() {}
	Pair(int a_, int b_) : a(a_), b(b_) {}
	bool operator < (const Pair &t) const {
		return (a != t.a ? a < t.a : b < t.b);
	}
};

Pair operator + (const Pair &a, const Pair &b) {
	return (Pair(a.a + b.a, a.b + b.b));
}

Pair operator - (const Pair &a, const Pair &b) {
	return (Pair(a.a - b.a, a.b - b.b));
}

Pair mp(int a, int b) {
	return Pair(a, b);
}

const int kMaxN = 100000;
int n, f[kMaxN], s[kMaxN], ind[kMaxN];
int q[kMaxN], qh, qt;
bool on[kMaxN], vis[kMaxN];
vector<int> t[kMaxN];
Pair g[kMaxN][2], h[kMaxN][2][2], ans;
int rg[kMaxN][2];
Pair rh[kMaxN][2][2], sol[kMaxN];
int idx;

void Solve(int st) {
	static int q[kMaxN];
	int qh = 0, qt = 0;
	q[qt ++] = st;
	while (qh < qt) {
		int u = q[qh ++];
		rg[u][1] = -1;
		for (vector<int>::iterator it = t[u].begin(); it != t[u].end(); ++ it)
			if (on[*it]) q[qt ++] = *it;
	}
	for (int i = qt - 1; i >= 0; -- i) {
		int u = q[i];
		for (vector<int>::iterator it = t[u].begin(); it != t[u].end(); ++ it)
			if (on[*it]) g[u][0] = g[u][0] + max(g[*it][0], g[*it][1]);
		for (vector<int>::iterator it = t[u].begin(); it != t[u].end(); ++ it)
			if (on[*it]) {
				Pair tmp = g[u][0] - max(g[*it][0], g[*it][1]) + g[*it][0] + mp(1, s[u] ^ s[*it]);
				if (g[u][1] < tmp) {
					g[u][1] = tmp;
					rg[u][1] = *it;
				}
			}
	}
}

void Get(int st, int a) {
	static int q[kMaxN], v[kMaxN];
	int qh = 0, qt = 0;
	v[qt] = a, q[qt ++] = st;
	while (qh < qt) {
		int u = q[qh], b = v[qh ++];
		if (b) sol[idx ++] = Pair(u, rg[u][1]);
		for (vector<int>::iterator it = t[u].begin(); it != t[u].end(); ++ it)
			if (on[*it]) {
				if (b == 0 || *it != rg[u][1]) {
					if (g[*it][0] < g[*it][1]) {
						v[qt] = 1;
						q[qt ++] = *it;
					}
					else {
						v[qt] = 0;
						q[qt ++] = *it;
					}
				}
				else {
					v[qt] = 0;
					q[qt ++] = *it;
				}
			}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &f[i], &s[i]);
		t[-- f[i]].push_back(i);
		++ ind[f[i]];
		-- s[i];
	}
	for (int i = 0; i < n; ++ i)
		if (!ind[i]) on[q[qt ++] = i] = true;
	while (qh < qt) {
		int u = q[qh ++];
		if (!(-- ind[f[u]])) on[q[qt ++] = f[u]] = true;
	}
	for (int i = 0; i < n; ++ i)
		if (!on[i] && !vis[i]) {
			qh = qt = 0;
			vis[q[qt ++] = i] = true;
			while (qh < qt) {
				int u = q[qh ++];
				if (!vis[f[u]]) vis[q[qt ++] = f[u]] = true;
			}
			Solve(q[0]);
			Solve(q[1]);
			rh[q[0]][0][0] = Pair(-1, -1);
			rh[q[0]][1][1] = Pair(-1, -1);
			h[q[0]][0][0] = g[q[0]][0];
			h[q[0]][1][1] = g[q[0]][1];
			h[q[0]][1][0] = h[q[0]][0][1] = mp(-0x3f3f3f3f, 0);
			h[q[1]][0][0] = h[q[0]][0][0] + g[q[1]][0], rh[q[1]][0][0] = Pair(0, 0);
			h[q[1]][0][1] = h[q[0]][1][1] + g[q[1]][0], rh[q[1]][0][1] = Pair(1, 1);
			h[q[1]][1][0] = h[q[0]][0][0] + g[q[1]][1], rh[q[1]][1][0] = Pair(0, 0);
			Pair aa = h[q[0]][1][1] + g[q[1]][1], bb = h[q[0]][0][0] + g[q[1]][0] + mp(1, s[q[0]] ^ s[q[1]]);
			if (aa < bb) {
				h[q[1]][1][1] = bb;
				rh[q[1]][1][1] = Pair(0, 0);
			}
			else {
				h[q[1]][1][1] = aa;
				rh[q[1]][1][1] = Pair(1, 1);
			}
			for (int i = 2; i < qt; ++ i) {
				Solve(q[i]);
				for (int j = 0; j < 2; ++ j)
					if (h[q[i - 1]][0][j] < h[q[i - 1]][1][j]) {
						h[q[i]][0][j] = h[q[i - 1]][1][j] + g[q[i]][0];
						rh[q[i]][0][j] = Pair(1, j);
					}
					else {
						h[q[i]][0][j] = h[q[i - 1]][0][j] + g[q[i]][0];
						rh[q[i]][0][j] = Pair(0, j);
					}
				for (int j = 0; j < 2; ++ j) {
					if (h[q[i]][1][j] < h[q[i - 1]][0][j] + g[q[i]][1]) {
						h[q[i]][1][j] = h[q[i - 1]][0][j] + g[q[i]][1];
						rh[q[i]][1][j] = Pair(0, j);
					}
					if (h[q[i]][1][j] < h[q[i - 1]][1][j] + g[q[i]][1]) {
						h[q[i]][1][j] = h[q[i - 1]][1][j] + g[q[i]][1];
						rh[q[i]][1][j] = Pair(1, j);
					}
					Pair aa = h[q[i - 1]][0][j] + mp(1, s[q[i]] ^ s[q[i - 1]]) + g[q[i]][0], bb = h[q[i - 1]][1][j] + g[q[i]][0];
					if (h[q[i]][1][j] < aa) {
						h[q[i]][1][j] = aa;
						rh[q[i]][1][j] = Pair(0, j);
					}
					if (h[q[i]][1][j] < bb) {
						h[q[i]][1][j] = bb;
						rh[q[i]][1][j] = Pair(1, j);
					}
				}
			}
			int a = 0, b = 0;
			Pair add = h[q[qt - 1]][0][0] + mp(1, s[q[qt - 1]] ^ s[q[0]]);
			if (add < h[q[qt - 1]][0][1]) {
				add = h[q[qt - 1]][0][1];
				a = 0, b = 1;
			}
			if (add < h[q[qt - 1]][1][0]) {
				add = h[q[qt - 1]][1][0];
				a = 1, b = 0;
			}
			if (add < h[q[qt - 1]][1][1]) {
				add = h[q[qt - 1]][1][1];
				a = 1, b = 1;
			}
			ans = ans + add;
			if (a == 0 && b == 0) sol[idx ++] = Pair(q[0], q[qt - 1]);
			for (int i = qt - 1; i >= 0; -- i) {
				Pair re = rh[q[i]][a][b];
				if (a == 0) Get(q[i], a);
				else {
					if (i == 0) Get(q[i], a);
					else {
						Pair tmp = h[q[i]][a][b] - g[q[i]][a];
						if (tmp.a == h[q[i - 1]][re.a][re.b].a && tmp.b == h[q[i - 1]][re.a][re.b].b) Get(q[i], a);
						else {
							Get(q[i], 0);
							sol[idx ++] = Pair(q[i], q[i - 1]);
						}
					}
				}
				a = re.a, b = re.b;
			}
		}
	printf("%d %d\n", ans.a, ans.b);
	for (int i = 0; i < idx; ++ i) printf("%d %d\n", sol[i].a + 1, sol[i].b + 1);
	return 0;
}
