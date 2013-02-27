#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100;
char buf[kMaxN + 1];
int n, seq[kMaxN + 1];
ll dp[kMaxN + 1][2][2];

int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for (int i = 0; i < n; ++ i) seq[i] = buf[i] - 'A';
	seq[n] = seq[0];
	ll ans = 0;
	for (int st = 0; st < 2; ++ st)
		for (int ed = 0; ed < 2; ++ ed) {
			memset(dp, 0, sizeof(dp));
			dp[0][st][ed] = 1;
			for (int i = 0; i < n; ++ i)
				for (int cur = 0; cur < 2; ++ cur)
					for (int pre = 0; pre < 2; ++ pre)
						if (dp[i][cur][pre]) {
							if ((seq[i] == 0 && (cur == 0 || pre == 0)) || (seq[i] == 1 && (cur == 1 && pre != 0)))
								dp[i + 1][0][cur] += dp[i][cur][pre];
							if ((seq[i] == 1 && ((cur == 1 && pre != 0) || (cur == 0))) || (seq[i] == 0 && (cur == 1 && pre == 0)))
								dp[i + 1][1][cur] += dp[i][cur][pre];
						}
			ans += dp[n][st][ed];
		}
	printf("%I64d\n", ans);
	return 0;
}
