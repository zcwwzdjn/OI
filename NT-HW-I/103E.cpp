#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 300;
int n, w[kMaxN], mat[kMaxN];
vector<int> num[kMaxN];
bool vis[kMaxN];

namespace flow {
#define OP(x) ((x) ^ 1)
	const int kMaxV = kMaxN + 2, kMaxE = (kMaxN + kMaxN * kMaxN) * 2;
	int cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cap[kMaxE];
	int s, t, label[kMaxV], start[kMaxV], q[kMaxV], qh, qt, stack[kMaxV], edge[kMaxV], stop;
	int maxflow;

	void Init(int s_, int t_) {
		cnt = 0;
		memset(begin, -1, sizeof(int) * (n + 2));
		s = s_, t = t_;
	}

	void AddEdge(int u, int v, int c) {
		next[cnt] = begin[u];
		begin[u] = cnt;
		end[cnt] = v;
		cap[cnt ++] = c;
	}

	void AddPair(int u, int v, int c) {
		AddEdge(u, v, c);
		AddEdge(v, u, 0);
	}

	bool Relabel() {
		qh = qt = 0;
		memset(label, -1, sizeof(label));
		for (label[s] = 0, start[s] = begin[s], q[qt ++] = s; qh < qt; ) {
			int u = q[qh ++];
			for (int now = begin[u], v; now != -1; now = next[now])
				if (cap[now] && label[v = end[now]] < 0) {
					label[v] = label[u] + 1;
					start[v] = begin[v];
					q[qt ++] = v;
				}
		}
		return (label[t] != -1);
	}

	void DoAug() {
		stop = 0;
		stack[stop ++] = s;
		while (stop) {
			int u = stack[stop - 1];
			if (u != t) {
				int &now = start[u], v;
				for ( ; now != -1; now = next[now])
					if (cap[now] && label[v = end[now]] == label[u] + 1) break;
				if (now >= 0) {
					stack[stop] = v;
					edge[stop ++] = now;
				}
				else {
					-- stop;
					label[u] = -1;
				}
			}
			else {
				int flow = kInf;
				for (int i = stop - 1; i >= 1; -- i)
					flow = min(flow, cap[edge[i]]);
				for (int i = stop - 1; i >= 1; -- i) {
					cap[edge[i]] -= flow, cap[OP(edge[i])] += flow;
					if (!cap[edge[i]]) stop = i;
				}
				maxflow += flow;
			}
		}
	}

	int Maxflow() {
		maxflow = 0;
		while (Relabel()) DoAug();
		return maxflow;
	}
#undef OP
}

bool Dfs(int u) {
	for (int i = 0, v; i < int(num[u].size()); ++ i)
		if (!vis[v = num[u][i]]) {
			vis[v] = true;
			if (mat[v] == -1 || Dfs(mat[v])) {
				mat[v] = u;
				return true;
			}
		}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i) {
		scanf("%d", &x);
		for (int y; x --; ) {
			scanf("%d", &y);
			num[i].push_back(y - 1);
		}
	}
	memset(mat, -1, sizeof(mat));
	for (int i = 0; i < n; ++ i) {
		memset(vis, false, sizeof(vis));
		Dfs(i);
	}
	for (int i = 0; i < n; ++ i) scanf("%d", &w[i]);
	flow::Init(n, n + 1);
	int ans = 0;
	for (int i = 0; i < n; ++ i)
		if (w[i] < 0) {
			ans += -w[i];
			flow::AddPair(n, i, -w[i]);
		}
		else if (w[i] > 0)
			flow::AddPair(i, n + 1, w[i]);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < int(num[i].size()); ++ j)
			if (mat[num[i][j]] != i) flow::AddPair(i, mat[num[i][j]], kInf);
	ans -= flow::Maxflow();
	printf("%d\n", -ans);
	return 0;
}
