#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kMaxM = 10000;
int n, m, root[kMaxN];
list<pair<int, int> > e[kMaxN];
pair<int, int> r[kMaxM];
vector<int> seq;
bool vis[kMaxN];
int deg[kMaxN];
bool used[kMaxM + 1];
vector<int> ans[2];

#define mp make_pair

int Root(int x) {
	return (x == root[x] ? x : root[x] = Root(root[x]));
}

void Dfs(int u, int d) {
	for (list<pair<int, int> >::iterator it = e[u].begin(), tmp; it != e[u].end(); ) {
		if (used[it->second]) {
			tmp = it;
			++ tmp;
			//e[u].erase(it);
			it = tmp;
		}
		else {
			int v = it->first, o = it->second;
			used[o] = true;
			tmp = it;
			++ tmp;
			//e[u].erase(it);
			it = tmp;
			Dfs(v, d);
			ans[d].push_back(o);
		}
	}
}

bool Solve(int u, int d) {
	seq.clear();
	for (int i = 0; i < n; ++ i)
		if (Root(i) == Root(u)) seq.push_back(i), vis[i] = true;
	int odd_cnt = 0;
	for (int i = 0; i < int(seq.size()); ++ i)
		odd_cnt += (deg[seq[i]] & 1);
	if (odd_cnt != 0 && odd_cnt != 2) return false;
	int sv;
	if (odd_cnt == 0) sv = seq[0];
	else {
		for (int i = 0; i < int(seq.size()); ++ i)
			if (deg[seq[i]] & 1) sv = seq[i];
	}
	Dfs(sv, d);
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &m);
	for (int i = 0, u, v; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		r[i] = mp(u - 1, v - 1);
		seq.push_back(u - 1);
		seq.push_back(v - 1);
	}
	sort(seq.begin(), seq.end());
	seq.resize(unique(seq.begin(), seq.end()) - seq.begin());
	n = seq.size();
	for (int i = 0; i < n; ++ i) root[i] = i;
	int bcnt = n;
	for (int i = 0; i < m; ++ i) {
		r[i].first = lower_bound(seq.begin(), seq.end(), r[i].first) - seq.begin();
		r[i].second = lower_bound(seq.begin(), seq.end(), r[i].second) - seq.begin();
		int u = Root(r[i].first), v = Root(r[i].second);
		if (u != v) {
			-- bcnt;
			root[u] = v;
		}
	}
	for (int i = 0; i < m; ++ i) {
		++ deg[r[i].first], ++ deg[r[i].second];
		e[r[i].first].push_back(mp(r[i].second, i));
		e[r[i].second].push_back(mp(r[i].first, i));
	}
	bool chk = false;
	if (bcnt > 2) puts("-1");
	else if (bcnt == 2) {
		bool res = true;
		int cnt = 0;
		for (int i = 0; i < n; ++ i)
			if (!vis[i])
				if (!Solve(i, cnt ++)) res = false;
		if (!res) puts("-1");
		else chk = true;
	}
	else {
		if (m == 1) puts("-1");
		else {
			int odd_cnt = 0;
			for (int i = 0; i < n; ++ i) odd_cnt += (deg[i] & 1);
			if (odd_cnt == 0 || odd_cnt == 2) {
				chk = true;
				Solve(0, 0);
				ans[1].push_back(ans[0].back());
				ans[0].pop_back();
			}
			else if (odd_cnt == 4) {
				chk = true;
				vector<int> sp;
				for (int i = 0; i < n; ++ i)
					if (deg[i] & 1) sp.push_back(i);
				e[sp[0]].push_back(mp(sp[1], m));
				e[sp[1]].push_back(mp(sp[0], m));
				++ deg[sp[0]], ++ deg[sp[1]];
				Solve(0, 0);
				while (ans[0].back() != m) {
					ans[1].push_back(ans[0].back());
					ans[0].pop_back();
				}
				ans[0].pop_back();
			}
		}
	}
	if (chk) {
		for (int h = 0; h < 2; ++ h) {
			printf("%d\n", ans[h].size());
			for (int i = 0; i < int(ans[h].size()); ++ i) {
				if (i) printf(" ");
				printf("%d", ans[h][i] + 1);
			}
			puts("");
		}
	}
	return 0;
}
