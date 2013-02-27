#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 100000, kMaxM = kMaxN - 1;
const int kMaxV = kMaxN, kMaxE = (kMaxN - 1)  * 2;
int n, l, r, R, seq[kMaxM], m, ans[3], sol[3];
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cost[kMaxE], ss;
void AddEdge(int u, int v, int c) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cost[cnt ++] = c;
}

bool vis[kMaxV];
int dcnt, inq[kMaxV], q[kMaxV], qh, qt, sz[kMaxV], w[kMaxV], pre[kMaxV];
int rec[kMaxV][2], sum[kMaxV], dis[kMaxV];

struct MonoQueue {
	int q[kMaxV][2], qh, qt;
	void init() {
		qh = qt = 0;
	}
	void push(int v, int p) {
		while (qh < qt && v >= q[qt - 1][0]) -- qt;
		q[qt][0] = v;
		q[qt ++][1] = p;
	}
	int ask(int p) {
		while (qh < qt && q[qh][1] < p) ++ qh;
		if (qh < qt) return q[qh][0];
		else return -kInf;
	}
	int ask2(int p) {
		while (qh < qt && q[qh][1] < p) ++ qh;
		if (qh < qt) return q[qh][1];
		else return -1;
	}
} mono;

int Find(int u) {
	++ dcnt;
	qh = qt = 0;
	pre[u] = -1;
	inq[q[qt ++] = u] = dcnt;
	while (qh < qt) {
		u = q[qh ++];
		sz[u] = w[u] = 0;
		for (int now = begin[u], v; now != -1; now = next[now])
			if (!vis[v = end[now]] && inq[v] != dcnt) {
				pre[v] = u;
				inq[q[qt ++] = v] = dcnt;
			}
	}
	for (int i = qt - 1; i >= 0; -- i) {
		u = q[i];
		++ sz[u];
		if (pre[u] != -1) {
			sz[pre[u]] += sz[u];
			w[pre[u]] = max(w[pre[u]], sz[u]);
		}
		w[u] = max(w[u], qt - sz[u]);
	}
	int res = q[0];
	for (int i = 1; i < qt; ++ i)
		if (w[q[i]] < w[res]) res = q[i];
	R = min(r, qt);
	ss = qt;
	return res;
}

void CalcDis(int lim, int u) {
	dis[u] = 1;
	++ dcnt;
	qh = qt = 0;
	inq[q[qt ++] = u] = dcnt;
	while (qh < qt) {
		u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (!vis[v = end[now]] && inq[v] != dcnt) {
				dis[v] = dis[u] + 1;
				sum[v] = sum[u] + (cost[now] >= lim ? 1 : -1);
				inq[q[qt ++] = v] = dcnt;
			}
	}
}

bool Check(int lim, int u) {
	for (int i = 0; i < ss; ++ i) {
		rec[i][0] = -kInf;
		rec[i][1] = -1;
	}
	rec[0][0] = 0, rec[0][1] = u;
	sol[0] = -kInf;
	for (int now = begin[u], t; now != -1; now = next[now])
		if (!vis[t = end[now]]) {
			sum[t] = (cost[now] >= lim ? 1 : -1);
			CalcDis(lim, t);	
			int tmp = qt;
			while (dis[q[qt - 1]] > R) -- qt;
			int v[2];
			v[0] = -kInf, v[1] = -1;
			for (int i = 0; i + dis[q[qt - 1]] <= R; ++ i) 
				if (rec[i][0] > v[0]) {
					v[0] = rec[i][0];
					v[1] = rec[i][1];
				}
			int las = R - dis[q[qt - 1]];
			while (qt && dis[q[qt - 1]] >= l) {
				while (las + 1 + dis[q[qt - 1]] <= R) {
					++ las;
					if (rec[las][0] > v[0]) {
						v[0] = rec[las][0];
						v[1] = rec[las][1];
					}
				}
				if (sum[q[qt - 1]] + v[0] > sol[0]) {
					sol[0] = sum[q[qt - 1]] + v[0];
					sol[1] = v[1];
					sol[2] = q[qt - 1];
				}
				-- qt;
			}
			if (qt) {
				mono.init();
				for (int i = l - dis[q[qt - 1]]; i <= R - dis[q[qt - 1]]; ++ i) mono.push(rec[i][0], i);
				las = R - dis[q[qt - 1]];
				while (qt) {
					while (las + 1 + dis[q[qt - 1]] <= R) {
						++ las;
						mono.push(rec[las][0], las);
					}
					v[1] = mono.ask2(l - dis[q[qt - 1]]);
					v[0] = rec[v[1]][0];
					if (sum[q[qt - 1]] + v[0] > sol[0]) {
						sol[0] = sum[q[qt - 1]] + v[0];
						sol[1] = rec[v[1]][1];
						sol[2] = q[qt - 1];
					}
					-- qt;
				}
			}
			for (int i = 0; i < tmp; ++ i)
				if (sum[q[i]] > rec[dis[q[i]]][0]) {
					rec[dis[q[i]]][0] = sum[q[i]];
					rec[dis[q[i]]][1] = q[i];
				}
		}
	return (sol[0] >= 0);
}

void Dfs(int u) {
	u = Find(u);
	vis[u] = true;
	if (l > R) return;
	int lb = 0, rb = m;
	while (lb + 1 < rb) {
		int mid = (lb + rb) >> 1;
		if (Check(seq[mid], u)) lb = mid;
		else rb = mid;
	}
	Check(seq[lb], u);
	if (seq[lb] > ans[0]) {
		memcpy(ans, sol, sizeof(ans));
		ans[0] = seq[lb];
	}
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!vis[v = end[now]]) Dfs(v);
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d%d", &n, &l, &r);
	for (int u, v, c, i = 0; i < n - 1; ++ i) {
		scanf("%d%d%d", &u, &v, &c);
		-- u, -- v;
		AddEdge(u, v, c);
		AddEdge(v, u, c);
		seq[m ++] = c;
	}
	sort(seq, seq + m);
	m = unique(seq, seq + m) - seq;
	ans[0] = -1;
	Dfs(0);
	printf("%d %d\n", ans[1] + 1, ans[2] + 1);
	return 0;
}
