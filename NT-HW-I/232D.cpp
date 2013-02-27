#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kMaxQ = 100000, kMaxM = (kMaxN - 1) * 2 + 1;
int n, o[kMaxN + 1], m, b[kMaxM + 1], r[kMaxM + 1];
int q, pos[kMaxM + 1], rec[kMaxM + 1];
vector<int> upper[kMaxN], lower[kMaxN];
int where[kMaxN];

struct Node {
	int v[2], p;
	bool operator == (const Node &t) const {
		return (v[0] == t.v[0] && v[1] == t.v[1]);
	}
} nd[kMaxM + 1], tp[kMaxM + 1];
int cnt[kMaxM + 1], rank[kMaxM + 1], sa[kMaxM + 1], height[kMaxM + 1];

struct Query {
	int l, r;
	int st, ed;
	int ans;
} cmd[kMaxQ];

struct IndexTree {
#define LB(x) ((x) & (-(x)))
	int v[kMaxM + 1];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	void add(int i) {
		if (!i) return;
		for ( ; i <= m; i += LB(i)) ++ v[i];
	}
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= LB(i)) res += v[i];
		return res;
	}
#undef LB
} idt;

namespace st {
	int dp[18][kMaxM + 1];
	int log2[kMaxM + 1];

	void Init() {
		log2[1] = 0;
		for (int i = 2; i <= m; ++ i) {
			log2[i] = log2[i - 1];
			if ((i & (i - 1)) == 0) ++ log2[i];
		}
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 1; i <= m; ++ i) dp[0][i] = height[i];
		for (int j = 1; j < 18; ++ j)
			for (int i = 1; i <= m; ++ i) {
				dp[j][i] = dp[j - 1][i];
				if (i + (1 << (j - 1)) <= m) dp[j][i] = min(dp[j][i], dp[j - 1][i + (1 << (j - 1))]);
			}
	}
	
	int Query(int l, int r) {
		int s = log2[r - l + 1];
		return min(dp[s][l], dp[s][r - (1 << s) + 1]);
	}
}

void RadixSort(int b) {
	for (int i = 1; i >= 0; -- i) {
		memset(cnt, 0, sizeof(int) * (b + 1));
		for (int j = 1; j <= m; ++ j) ++ cnt[nd[j].v[i]];
		for (int j = 1; j <= b; ++ j) cnt[j] += cnt[j - 1];
		for (int j = m; j >= 1; -- j) tp[cnt[nd[j].v[i]] --] = nd[j];
		memcpy(nd, tp, sizeof(Node) * (m + 1));
	}
	for (int i = 1, j = 1, k = 1; i <= m; i = j, ++ k)
		while (j <= m && nd[j] == nd[i]) rank[nd[j ++].p] = k;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf("%d", &o[i]);
	scanf("%d", &q);
	if (n == 1) {
		for (int i = 0; i < q; ++ i) puts("0");
		return 0;
	}
	m = n - 1;
	for (int i = 1; i <= m; ++ i) r[i] = o[i] - o[i + 1];
	r[0] = m;
	for (int i = 1; i <= m; ++ i) r[++ r[0]] = o[i + 1] - o[i];
	sort(r + 1, r + r[0] + 1);
	r[0] = unique(r + 1, r + r[0] + 1) - (r + 1);
	for (int i = 1; i <= m; ++ i) b[i] = lower_bound(r + 1, r + r[0] + 1, o[i] - o[i + 1]) - r;
	b[m + 1] = r[0] + 1;
	for (int i = 1; i <= m; ++ i) pos[m + 1 + i] = i, b[m + 1 + i] = lower_bound(r + 1, r + r[0] + 1, o[i + 1] - o[i]) - r;
	m = m * 2 + 1;
	for (int i = 1; i <= m; ++ i) {
		nd[i].v[0] = b[i], nd[i].v[1] = 0;
		nd[i].p = i;
	}
	RadixSort(r[0] + 1);
	for (int s = 1; s < m; s <<= 1) {
		for (int i = 1; i <= m; ++ i) {
			nd[i].v[0] = rank[i], nd[i].v[1] = (i + s <= m ? rank[i + s] : 0);
			nd[i].p = i;
		}
		RadixSort(m);
	}
	for (int i = 1; i <= m; ++ i) sa[rank[i]] = i;
	for (int i = 1; i <= m; ++ i) {
		rec[i] = pos[sa[i]];
		where[rec[i]] = i;
	}
	for (int i = 1, j, k = 0; i <= m; height[rank[i ++]] = k)
		for (k ? -- k : 0, j = sa[rank[i] - 1]; b[i + k] == b[j + k]; ++ k);
	st::Init();
	for (int i = 0; i < q; ++ i) {
		scanf("%d%d", &cmd[i].l, &cmd[i].r);
		if (cmd[i].l != cmd[i].r) {
			int l = cmd[i].l, r = cmd[i].r - 1, s = r - l + 1;
			int p = rank[l];
			int lb = 0, rb = p;
			while (lb + 1 < rb) {
				int mid = (lb + rb) >> 1;
				if (st::Query(mid + 1, p) >= s) rb = mid;
				else lb = mid;
			}
			int st = rb;
			lb = p, rb = m + 1;
			while (lb + 1 < rb) {
				int mid = (lb + rb) >> 1;
				if (st::Query(p + 1, mid) >= s) lb = mid;
				else rb = mid;
			}
			int ed = lb;
			cmd[i].st = st, cmd[i].ed = ed;
			if (r + 2 < n) upper[r + 2].push_back(i);
			if (l - s - 1 >= 1) lower[l - s - 1].push_back(i);
		}
		else cmd[i].ans = n - 1;
	}
	idt.clear();
	for (int i = n - 1; i >= 1; -- i) {
		idt.add(where[i]);
		for (vector<int>::iterator it = upper[i].begin(); it != upper[i].end(); ++ it) {
			int j = *it;
			cmd[j].ans += idt.sum(cmd[j].ed) - idt.sum(cmd[j].st - 1);
		}
	}
	idt.clear();
	for (int i = 1; i <= n - 1; ++ i) {
		idt.add(where[i]);
		for (vector<int>::iterator it = lower[i].begin(); it != lower[i].end(); ++ it) {
			int j = *it;
			cmd[j].ans += idt.sum(cmd[j].ed) - idt.sum(cmd[j].st - 1);
		}
	}
	for (int i = 0; i < q; ++ i) printf("%d\n", cmd[i].ans);
	return 0;
}
