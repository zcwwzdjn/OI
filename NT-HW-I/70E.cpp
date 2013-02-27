#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 180;
int n, k, d[kMaxN], pre[kMaxN], dd[kMaxN][kMaxN];
bool par[kMaxN][kMaxN];
int cnt, begin[kMaxN], end[(kMaxN - 1) << 1], next[(kMaxN - 1) << 1];
int seq[kMaxN], seq_idx, lb[kMaxN], rb[kMaxN];
vector<int> tr[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs0(int u, int p) {
	pre[u] = p;
	seq[seq_idx ++] = u;
	lb[u] = seq_idx - 1;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (p != (v = end[now])) {
			tr[u].push_back(v);
			Dfs0(v, u);
		}
	rb[u] = seq_idx - 1;
}

int Dfs1(int);
int Dfs2(int, int, int);

int rec1[kMaxN];
vector<pair<int, int> > rec2[kMaxN][kMaxN][kMaxN];

int Dfs1(int u) {
	static int memo[kMaxN];
	static bool done[kMaxN];	
	if (done[u]) return memo[u];
	done[u] = true;
	int &res = memo[u];
	res = 0x3f3f3f3f;
	for (int i = lb[u]; i <= rb[u]; ++ i) {
		int tmp = Dfs2(u, seq[i], u) + k;
		if (tmp < res) {
			res = tmp;
			rec1[u] = seq[i];
		}
	}
	return res;
}

int Dfs2(int f, int g, int u) {
	static int memo[kMaxN][kMaxN][kMaxN];
	static bool done[kMaxN][kMaxN][kMaxN];
	if (done[f][g][u]) return memo[f][g][u];
	done[f][g][u] = true;
	int &res = memo[f][g][u];
	res = d[dd[g][u]];
	for (vector<int>::iterator it = tr[u].begin(); it != tr[u].end(); ++ it) {
		int v = *it;
		if (par[g][v]) res += Dfs2(f, g, v), rec2[f][g][u].push_back(make_pair(v, 0));
		else {
			int t0 = Dfs2(f, g, v);
			int t1 = Dfs1(v);
			if (t0 < t1) rec2[f][g][u].push_back(make_pair(v, 0)), res += t0;
			else rec2[f][g][u].push_back(make_pair(v, 1)), res += t1;
		}
	}
	return res;
}

void Dfs3(int);
void Dfs4(int, int, int);

vector<int> cho;

void Dfs3(int u) {
	cho.push_back(rec1[u]);
	Dfs4(u, rec1[u], u);
}

void Dfs4(int f, int g, int u) {
	for (vector<pair<int, int> >::iterator it = rec2[f][g][u].begin(); it != rec2[f][g][u].end(); ++ it) {
		int v = it->first;
		if (it->second == 0) Dfs4(f, g, v);
		else Dfs3(v);
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; ++ i) scanf("%d", &d[i]);
	memset(begin, -1, sizeof(begin));
	for (int u, v, i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	Dfs0(0, -1);
	for (int i = 0; i < n; ++ i) {
		int t = i;
		while (t != -1) {
			par[i][t] = true;
			t = pre[t];
		}
	}
	for (int i = 0; i < n; ++ i) {
		static int q[kMaxN];
		int qh = 0, qt = 0;
		q[qt ++] = i;
		while (qh < qt) {
			int u = q[qh ++];
			for (int now = begin[u], v; now != -1; now = next[now])
				if ((v = end[now]) != i && dd[i][v] == 0) {
					dd[i][v] = dd[i][u] + 1;
					q[qt ++] = v;
				}
		}
	}
	printf("%d\n", Dfs1(0));
	Dfs3(0);
	static int q[kMaxN], b[kMaxN];
	int qh = 0, qt = 0;
	memset(b, -1, sizeof(b));
	for (int i = 0; i < int(cho.size()); ++ i) {
		q[qt ++] = cho[i];
		b[cho[i]] = cho[i];
	}
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (b[v = end[now]] == -1) {
				b[v] = b[u];
				q[qt ++] = v;
			}
	}
	for (int i = 0; i < n; ++ i) {
		if (i) printf(" ");
		printf("%d", b[i] + 1);
	}
	puts("");
	return 0;
}
