#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 2000, kMaxM = kMaxN * 2 - 1, kMaxL = 500;
int n, k, seq[kMaxN], len[kMaxN], lcp[kMaxN];
char dna[kMaxN][kMaxL + 1];
int dp[kMaxM][kMaxN + 1];
int rec[kMaxN][kMaxN], cnt;

bool Cmp(const int &a, const int &b) {
	return (strcmp(dna[a], dna[b]) < 0);
}

void Dfs(int l, int r) {
	rec[l][r] = cnt ++;
	if (l < r) {
		int p = min_element(lcp + l + 1, lcp + r + 1) - lcp;
		Dfs(l, p - 1), Dfs(p, r);
		int lson = rec[l][p - 1], rson = rec[p][r];
		int lsz = p - l, rsz = r - p + 1;
		int far = rec[l][r];
		for (int i = 0; i <= lsz; ++ i)
			for (int j = 0; j <= rsz; ++ j)
				dp[far][i + j] = max(dp[far][i + j], dp[lson][i] + dp[rson][j] + i * j * lcp[p]);
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i) {
		scanf("%s", dna[i]);
		seq[i] = i;
		len[i] = strlen(dna[i]);
	}
	sort(seq, seq + n, Cmp);
	for (int i = 1; i < n; ++ i) {
		int upper = min(len[seq[i - 1]], len[seq[i]]);
		while (lcp[i] < upper && dna[seq[i - 1]][lcp[i]] == dna[seq[i]][lcp[i]])
			++ lcp[i];
	}
	memset(rec, -1, sizeof(rec));
	Dfs(0, n - 1);
	printf("%d\n", dp[0][k]);
	return 0;
}
