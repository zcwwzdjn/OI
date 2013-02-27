#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kInf = 0x3f3f3f3f;
const int kMaxN = 2000, kMaxM = 2000;
const int kMaxL = 1000000, kMaxS = 2000;
int n, m, s, l[kMaxN + 1], r[kMaxN + 1], len[kMaxN + 1];
int seq[kMaxM + 1], sum[kMaxM + 1];
char base[kMaxL + 2];
char str[kMaxS + 2];
int pos[26];
int next[26][kMaxL + 1];
int hyper_next[26][kMaxM + 1];
int dp[kMaxS + 1][kMaxS + 1];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		l[i] = r[i - 1] + 1;
		scanf("%s", base + l[i]);
		r[i] = l[i] + (len[i] = strlen(base + l[i])) - 1;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++ i) {
		scanf("%d", &seq[i]);
		sum[i] = sum[i - 1] + len[seq[i]];
	}
	scanf("%s", str + 1);
	s = strlen(str + 1);
	for (int i = 1; i <= n; ++ i) {
		for (int k = 0; k < 26; ++ k) pos[k] = len[i] + 1;
		for (int j = r[i]; j >= l[i]; -- j) {
			pos[base[j] - 'a'] = j - l[i] + 1;
			for (int k = 0; k < 26; ++ k) next[k][j] = pos[k];
		}
	}
	for (int k = 0; k < 26; ++ k) pos[k] = m + 1;
	for (int j = m; j >= 1; -- j)
		for (int k = 0; k < 26; ++ k) {
			if (next[k][l[seq[j]]] != len[seq[j]] + 1) pos[k] = j;
			hyper_next[k][j] = pos[k];
		}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= s; ++ i) {
		dp[i][0] = dp[i - 1][0];
		for (int j = 1; j <= i; ++ j) {
			dp[i][j] = dp[i - 1][j];
			if (dp[i - 1][j - 1] != kInf) {
				int t = str[i] - 'a';
				int prefix = dp[i - 1][j - 1];
				int belong = lower_bound(sum + 1, sum + m + 1, prefix) - sum;
				int index = prefix - sum[belong - 1];
				if (index == len[seq[belong]] || next[t][l[seq[belong]] + index] > len[seq[belong]]) {
					if (belong < m && hyper_next[t][belong + 1] <= m) {
						int nxt = hyper_next[t][belong + 1];
						dp[i][j] = min(dp[i][j], sum[nxt - 1] + next[t][l[seq[nxt]]]);
					}
				}
				else {
					dp[i][j] = min(dp[i][j], prefix + next[t][l[seq[belong]] + index] - index);
				}
			}
		}
	}
	int res = 0;
	for (int j = 1; j <= s; ++ j)
		if (dp[s][j] <= sum[m]) res = max(res, j);
	printf("%d\n", res);
	return 0;
}
