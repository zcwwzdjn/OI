#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 700, kMaxM = (kMaxN - 1) * 2;
int n, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int sz[kMaxN + 1];

struct Int {
	static const int kMaxD = 20;
	static const int kN = 1000000000;
	int dig, num[kMaxD];
	Int() : dig(0) {
		memset(num, 0, sizeof(num));
	}
	Int(int x) {
		memset(num, 0, sizeof(num));
		num[(dig = 1) - 1] = x;
	}
	void print() {
		printf("%d", num[dig - 1]);
		for (int i = dig - 2; i >= 0; -- i) printf("%09d", num[i]);
		puts("");
	}
} dp[kMaxN + 1][kMaxN + 1], dpm[kMaxN + 1], f[2][kMaxN + 1], ll[kMaxN + 1], rr[kMaxN + 2];

Int operator * (const Int &a, const Int &b) {
	Int c;
	for (int i = 0; i < a.dig; ++ i)
		for (int j = 0; j < b.dig; ++ j) {
			long long t = (long long)a.num[i] * b.num[j];
			c.num[i + j + 1] += (c.num[i + j] + t) / Int::kN;
			c.num[i + j] = (c.num[i + j] + t) % Int::kN;
		}
	c.dig = a.dig + b.dig;
	while (!c.num[c.dig - 1]) -- c.dig;
	return c;
}

bool operator < (const Int &a, const Int &b) {
	if (a.dig < b.dig) return true;
	if (a.dig > b.dig) return false;
	for (int i = a.dig - 1; i >= 0; -- i) {
		if (a.num[i] < b.num[i]) return true;
		if (a.num[i] > b.num[i]) return false;
	}
	return false;
}

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs(int u, int p) {
	int sc = 0;
	vector<int> seq;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (p != (v = end[now])) {
			Dfs(v, u);
			sz[u] += sz[v];
			seq.push_back(v);
			++ sc;
		}
	++ sz[u];
	int des = 0, src = 1;
	for (int i = 1; i <= sc + 1; ++ i) f[des][i] = 0;
	f[des][1] = 1;
	for (int now = begin[u], v; now != -1; now = next[now]) if (p != (v = end[now])) {
		des ^= 1, src ^= 1;
		for (int j = 1; j <= sc + 1; ++ j) f[des][j] = f[src][j] * dpm[v];
		for (int j = 2; j <= sc + 1; ++ j)
			f[des][j] = max(f[des][j], f[src][j - 1] * dp[v][1]);
	}
	for (int j = 1; j <= sc + 1; ++ j) dp[u][j] = f[des][j];
	ll[0] = 1;
	rr[sc + 1] = 1;
	for (int i = 1; i <= sc; ++ i) ll[i] = ll[i - 1] * dpm[seq[i - 1]];
	for (int i = sc; i >= 1; -- i) rr[i] = rr[i + 1] * dpm[seq[i - 1]];
	for (int i = 1; i <= sc; ++ i)
		for (int j = 2; j <= sz[u]; ++ j)
			dp[u][j] = max(dp[u][j], ll[i - 1] * rr[i + 1] * dp[seq[i - 1]][j - 1]);
	for (int j = 1; j <= sz[u]; ++ j) dpm[u] = max(dpm[u], dp[u][j] * j);
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int u, v, i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v), AddEdge(v, u);
	}
	Dfs(0, -1);
	dpm[0].print();
	return 0;
}
