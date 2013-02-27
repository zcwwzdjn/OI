#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <functional>
#include <algorithm>

using namespace std;

const int kMaxN = 1000, kMaxM = 1000, kMaxK = 1000;
int n, m, k, v[kMaxM][kMaxK], s[kMaxM], cnt[kMaxM], hav[kMaxM];
pair<int, int> seq[kMaxK];
double c[kMaxK + 1][kMaxK + 1];
double dp[2][kMaxK + 1];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i) {
		scanf("%d", &s[i]);
		for (int j = 0; j < s[i]; ++ j) {
			scanf("%d", &v[i][j]);
			seq[k ++] = make_pair(v[i][j], i);
		}
		sort(v[i], v[i] + s[i], greater<int>());
	}
	c[0][0] = 1.0;
	for (int i = 1; i <= k; ++ i) {
		c[i][0] = 1.0;
		for (int j = 1; j <= i; ++ j)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	sort(seq, seq + k, greater<pair<int, int> >());
	int r = n - 1;
	while (r > 0 && seq[r - 1].first == seq[r].first) -- r;
	for (int i = 0; i < r; ++ i) ++ cnt[seq[i].second];
	int val = seq[r].first, cho = n - r;
	for (int i = 0; i < m; ++ i)
		for (int j = 0; j < s[i]; ++ j) hav[i] += (v[i][j] == val);
	int des = 0, src = 1;
	dp[des][0] = 1.0;
	for (int i = 0, sum = 0; i < m; ++ i) {
		des ^= 1, src ^= 1;
		for (int j = 0; j <= sum; ++ j) dp[des][j] = 0.0;
		for (int j = 0; j <= sum; ++ j)
			for (int k = 0; k <= hav[i]; ++ k)
				dp[des][j + k] += dp[src][j] / c[s[i]][cnt[i] + k];
		sum = min(sum + hav[i], cho);
	}
	int tot = 0;
	for (int i = 0; i < m; ++ i) tot += hav[i];
	printf("%.9lf\n", dp[des][cho] / c[tot][cho]);
	return 0;
}
