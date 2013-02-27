#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 300, kMaxM = 300;
int n, m, col[kMaxN][kMaxM], mat[kMaxN][kMaxM];
const int kMaxV = kMaxN * kMaxM;
int root[kMaxV], sz[kMaxV], co[kMaxV];
int seq[kMaxN * kMaxM * 2 + 1], idx;
queue<int> q;
int where[kMaxN * kMaxM * 2];
vector<int> on[kMaxN * kMaxM * 2];

int Root(int x) {
	if (x == root[x]) return x;
	else {
		int t = Root(root[x]);
		co[x] = co[t];
		root[x] = t;
		return t;
	}
}

void Union(int u, int v) {
	sz[u] += sz[v];
	root[v] = u;
	co[v] = co[u];
}

int dis[kMaxN * kMaxM];
bool Cmp(const int &a, const int &b) {
	return (dis[a] < dis[b]);
}

int Calc(int dx, int dy) {
	swap(dx, dy);
	int d = max(abs(dx), abs(dy));
	int res = (2 * d - 1) * (2 * d - 1);
	if (dx == -d && dy == -d) return ((2 * d + 1) * (2 * d + 1));
	if (dy == -d) {
		return (res + (dx - (-(d - 1))) + 1);
	}
	res += d - (-(d - 1));
	if (dx == d) {
		return (res + (dy - (-d) + 1));
	}
	res += d - (-d);
	if (dy == d) {
		return (res + (d - dx + 1));
	}
	res += d - (-d);
	return (res + (d - dy + 1));
}

int main() {
	scanf("%d%d", &n, &m);
	seq[idx ++] = 0;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			scanf("%d", &col[i][j]);
			seq[idx ++] = col[i][j];
		}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			scanf("%d", &mat[i][j]);
			if (mat[i][j] != -1) seq[idx ++] = mat[i][j];
		}
	sort(seq, seq + idx);
	idx = unique(seq, seq + idx) - seq;
	for (int i = 0; i < idx; ++ i) where[i] = -1;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			col[i][j] = lower_bound(seq, seq + idx, col[i][j]) - seq;
			root[i * m + j] = i * m + j;
			sz[i * m + j] = 1;
			co[i * m + j] = col[i][j];
			if (where[col[i][j]] == -1) where[col[i][j]] = i * m + j;
			else Union(where[col[i][j]], i * m + j);
		}
	int x, y;
	scanf("%d%d", &x, &y);
	-- x, -- y;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			if (mat[i][j] != -1) {
				mat[i][j] = lower_bound(seq, seq + idx, mat[i][j]) - seq;
				if (i != x || j != y)
					on[col[i][j]].push_back(i * m + j);
			}
		}
	q.push(x * m + y);
	long long ans = 0;
	while (q.size()) {
		int ux = q.front() / m, uy = q.front() % m;
		q.pop();
		int c = co[Root(ux * m + uy)];
		if (c == 0 || c == mat[ux][uy]) continue;
		if (on[c].size()) {
			int sz = on[c].size();
			for (int i = 0; i < sz; ++ i) {
				int v = on[c][i];
				int vx = v / m, vy = v % m;
				dis[v] = Calc(vx - ux, vy - uy);
			}
			sort(on[c].begin(), on[c].end(), Cmp);
			for (int i = 0; i < sz; ++ i) q.push(on[c][i]);
			on[c].clear();
		}
		ans += sz[where[c]];
		if (where[mat[ux][uy]] == -1) {
			where[mat[ux][uy]] = where[c];
			co[where[c]] = mat[ux][uy];
			where[c] = -1;
		}
		else {
			Union(where[mat[ux][uy]], where[c]);
			where[c] = -1;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
