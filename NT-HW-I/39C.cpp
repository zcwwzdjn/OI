#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 2000;
int n, a[kMaxN + 1];
int t[kMaxN], p[kMaxN], h[kMaxN + 2], *hh = h + 1, tc, g[kMaxN + 2], *gg = g + 1;
vector<int> cho[kMaxN + 1];
bool fir = true;

struct Node {
	long long l, r;
   	int x;
} s[kMaxN + 1];

bool CmpS(const int &a, const int &b) {
	return ((s[a].r - s[a].l) < (s[b].r - s[b].l));
}

bool CmpRR(const Node &a, const Node &b) {
	return (a.r < b.r);
}

void Dfs(int u) {
	for (vector<int>::iterator it = cho[u].begin(); it != cho[u].end(); ++ it) {
		if (!fir) printf(" "); else fir = false;
		printf("%d", s[*it].x + 1);
		Dfs(*it);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0, c, r; i < n; ++ i) {
		scanf("%d%d", &c, &r);
		s[i].l = c - r, s[i].r = c + r, s[i].x = i;
	}
	s[n].l = INT_MIN, s[n].r = INT_MAX, s[n].x = n;
	++ n;
	sort(s, s + n, CmpRR);
	int seq[kMaxN + 1];
	for (int i = 0; i < n; ++ i) seq[i] = i;
	sort(seq, seq + n, CmpS);
	for (int i = 0; i < n; ++ i) {
		int u = seq[i];
		tc = 0;
		for (int v = 0; v < n; ++ v)
			if (s[v].l >= s[u].l && s[v].r <= s[u].r && v != u) t[tc ++] = v;
		a[u] = 1;
		if (tc) {
			for (int j = -1; j < tc; ++ j) hh[j] = INT_MIN, gg[j] = 0;
			for (int j = 0; j < tc; ++ j) p[j] = -1;
			for (int j = 1; j < tc; ++ j) {
				int lb = 0, rb = j;
				while (lb + 1 < rb) {
					int mid = (lb + rb) >> 1;
					if (s[t[mid]].r <= s[t[j]].l) lb = mid;
					else rb = mid;
				}
				if (s[t[lb]].r <= s[t[j]].l) p[j] = lb;
			}
			hh[-1] = 0;
			for (int j = 0; j < tc; ++ j) {
				hh[j] = hh[j - 1], gg[j] = 0;
				if (hh[p[j]] + a[t[j]] > hh[j]) {
					hh[j] = hh[p[j]] + a[t[j]];
					gg[j] = 1;
				}
			}
			int end = tc - 1;
			while (end != -1) {
				if (gg[end]) cho[u].push_back(t[end]), end = p[end];
				else -- end;
			}
			a[u] += hh[tc - 1];
		}
	}
	printf("%d\n", a[n - 1] - 1);
	Dfs(n - 1);
	puts("");
	return 0;
}
