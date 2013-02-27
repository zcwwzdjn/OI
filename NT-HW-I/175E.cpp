#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

const double kEps = 1E-9;
const int kMaxN = 20, kMaxM = 11;
int nf, ne, ns, rf, re, rs, df, de;
double ans, lenf, lene, lens;
int cnt[13];
double dp[2][kMaxN + 1][kMaxN + 1];
double ff[13], ee[13];
pair<double, int> seq[kMaxN << 1 | 1];
int buf[(kMaxN << 1) + 2], *sum = buf + 1; 

void Solve() {
	int t = 0;
	for (int i = 0; i < kMaxM; ++ i)
		for (int j = 1; j <= cnt[i]; ++ j) {
			seq[t ++] = make_pair(i - lens, 1);
			seq[t ++] = make_pair(i + lens + kEps, -1);
		}
	seq[t ++] = make_pair(1E10, 0);
	sort(seq, seq + t);
	sum[-1] = 0;
	for (int i = 0; i < t; ++ i) sum[i] = sum[i - 1] + seq[i].second;
	for (int i = 0; i < kMaxM; ++ i) {
		double lb = i - lenf, rb = i + lenf;
		ff[i] = 0.0;
		while (lb + kEps < rb) {
			int q = lower_bound(seq, seq + t, make_pair(lb, -1)) - seq;
			ff[i] += (sum[q - 1] + 1) * (min(rb, seq[q].first) - lb) * df;
			lb = seq[q].first + kEps;
		}
	}
	for (int i = 0; i < kMaxM; ++ i) {
		double lb = i - lene, rb = i + lene;
		ee[i] = 0.0;
		while (lb + kEps < rb) {
			int q = lower_bound(seq, seq + t, make_pair(lb, -1)) - seq;
			ee[i] += (sum[q - 1] + 1) * (min(rb, seq[q].first) - lb) * de;
			lb = seq[q].first + kEps;
		}
	}
	int des = 0, src = 1;
	for (int i = 0; i <= nf; ++ i)
		for (int j = 0; j <= ne; ++ j) dp[des][i][j] = 0.0;
	for (int k = 0; k < kMaxM; ++ k) {
		if (cnt[k] == 2) continue;
		des ^= 1, src ^= 1;
		for (int i = 0; i <= nf; ++ i)
			for (int j = 0; j <= ne; ++ j) {
				dp[des][i][j] = dp[src][i][j];
				for (int l = 1; l <= 2 - cnt[k]; ++ l) {
					if (i >= l) dp[des][i][j] = max(dp[des][i][j], dp[src][i - l][j] + l * ff[k]);
					if (j >= l) dp[des][i][j] = max(dp[des][i][j], dp[src][i][j - l] + l * ee[k]);
				}
				if (cnt[k] == 0 && i >= 1 && j >= 1) dp[des][i][j] = max(dp[des][i][j], dp[src][i - 1][j - 1] + ff[k] + ee[k]);
			}
	}
	ans = max(ans, dp[des][nf][ne]);
}

void Dfs(int step, int rest) {
	if (step == 10) {
		if (!rest) Solve();
		return;
	}
	for (int i = 0; i <= 2; ++ i)
		if (rest >= i) {
			cnt[step] = i;
			Dfs(step + 1, rest - i);
		}
}

int main() {
	scanf("%d%d%d%d%d%d%d%d", &nf, &ne, &ns, &rf, &re, &rs, &df, &de);
	lenf = sqrt(rf * rf - 1);
	lene = sqrt(re * re - 1);
	lens = sqrt(rs * rs - 1);
	Dfs(0, ns);
	printf("%.8lf\n", ans);
	return 0;
}
