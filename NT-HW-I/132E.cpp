#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 250, kMaxM = 26;
int n, m, seq[kMaxN], val[kMaxN];
int pos[kMaxN], pre[kMaxN];
vector<pair<int, int> > sol;

namespace flow {
	const int kMaxV = kMaxN * 2 + 3, kMaxE = (kMaxN * 2 + (kMaxN - 1) * kMaxN / 2 + kMaxN + 1) * 2;
	int sv, tv, cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cap[kMaxE], cost[kMaxE];
	int dis[kMaxV], pre[kMaxV];
	bool inq[kMaxV];
	queue<int> q;
	int maxflow, mincost;

	void Init(int s, int t) {
		sv = s, tv = t;
		cnt = 0, memset(begin, -1, sizeof(begin));
	}

	void AddEdge(int u, int v, int c, int w) {
		next[cnt] = begin[u];
		begin[u] = cnt;
		end[cnt] = v;
		cap[cnt] = c;
		cost[cnt ++] = w;
	}

	void AddPair(int u, int v, int c, int w) {
		AddEdge(u, v, c, w);
		AddEdge(v, u, 0, -w);
	}

	bool Spfa() {
		memset(dis, 0x3f, sizeof(dis));
		dis[sv] = 0, inq[sv] = true, q.push(sv);
		while (q.size()) {
			int u = q.front();
			q.pop(), inq[u] = false;
			for (int now = begin[u], v; now != -1; now = next[now])
				if (cap[now] && dis[v = end[now]] > dis[u] + cost[now]) {
					dis[v] = dis[u] + cost[now];
					pre[v] = now;
					if (!inq[v]) inq[v] = true, q.push(v);
				}
		}
		return (dis[tv] != kInf);
	}

	void DoAug() {
		int flow = kInf;
	   	for (int i = tv; i != sv; i = end[pre[i] ^ 1])
			flow = min(flow, cap[pre[i]]);	
		for (int i = tv; i != sv; i = end[pre[i] ^ 1])
			cap[pre[i]] -= flow, cap[pre[i] ^ 1] += flow;
		maxflow += flow;
		mincost += flow * dis[tv];
	}

	int Mincost() {
		maxflow = 0, mincost = 0;
		while (Spfa()) {
			if (dis[tv] > 0) break;
			DoAug();
		}
		return mincost;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &seq[i]);
		val[i] = __builtin_popcount(seq[i]);
	}
	flow::Init(n * 2 + 1, n * 2 + 2);
	flow::AddPair(n * 2 + 1, n * 2, m, 0);
	for (int i = 0; i < n; ++ i) {
		flow::AddPair(i, i + n, 1, -100000);
		flow::AddPair(n * 2, i, 1, val[i]);
		flow::AddPair(i + n, n * 2 + 2, 1, 0);
		for (int j = i + 1; j < n; ++ j)
			flow::AddPair(i + n, j, 1, seq[i] == seq[j] ? 0 : val[j]);
	}
	int ans = flow::Mincost() + n * 100000;
	memset(pre, -1, sizeof(pre));
	memset(pos, -1, sizeof(pos));
	for (int i = 0, now = flow::begin[n * 2]; now != -1; now = flow::next[now])
		if (flow::end[now] != n * 2 + 1 && !flow::cap[now]) pos[flow::end[now]] = i ++;
	for (int i = 0; i < n; ++ i) {
		if (pre[i] == -1 || seq[pre[i]] != seq[i]) sol.push_back(make_pair(seq[i], pos[i]));
		sol.push_back(make_pair(0, pos[i]));
		for (int now = flow::begin[i + n]; now != -1; now = flow::next[now])
			if (flow::end[now] != i && flow::end[now] != n * 2 + 2 && !flow::cap[now]) {
				pos[flow::end[now]] = pos[i];
				pre[flow::end[now]] = i;
				break;
			}
	}
	printf("%d %d\n", sol.size(), ans);
	for (int i = 0; i < int(sol.size()); ++ i) {
		assert(sol[i].second >= 0 && sol[i].second < m);
		if (sol[i].first == 0) printf("print(%c)\n", 'a' + sol[i].second);
		else printf("%c=%d\n", 'a' + sol[i].second, sol[i].first);
	}
	return 0;
}
