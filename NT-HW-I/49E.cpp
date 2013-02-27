#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 50;
char s1[kMaxN + 2], s2[kMaxN + 2];
int l1, l2, n;
int tr[26][26], dp[kMaxN + 1][kMaxN + 1];
int t1[kMaxN + 1][kMaxN + 1], t2[kMaxN + 1][kMaxN + 1];

int ctz(int mask) {
	int res = -1;
	while (mask) {
		++ res;
		mask >>= 1;
	}
	return res;
}

void Solve(char *s, int l, int t[kMaxN + 1][kMaxN + 1]) {
	for (int i = 1; i <= l; ++ i) t[i][i] = 1 << (s[i] - 'a');
	for (int k = 2; k <= l; ++ k)
		for (int i = 1; i <= l - k + 1; ++ i) {
			int j = i + k - 1;
			for (int o = i; o < j; ++ o) {
				int p = t[i][o];
				while (p) {
					int pnow = p & -p;
					p ^= pnow;
					int q = t[o + 1][j];
					while (q) {
						int qnow = q & -q;
						q ^= qnow;
						t[i][j] |= tr[ctz(pnow)][ctz(qnow)];
					}
				}
			}
		}
}

int main() {
	scanf("%s%s", s1 + 1, s2 + 1);
	l1 = strlen(s1 + 1), l2 = strlen(s2 + 1);
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static char buf[8];
		scanf("%s", buf);
		tr[buf[3] - 'a'][buf[4] - 'a'] |= 1 << (buf[0] - 'a');
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	Solve(s1, l1, t1);
	Solve(s2, l2, t2);
	for (int i = 1; i <= l1; ++ i)
		for (int j = 1; j <= l2; ++ j)
			for (int ii = 0; ii < i; ++ ii)
				for (int jj = 0; jj < j; ++ jj)
					if (t1[ii + 1][i] & t2[jj + 1][j]) dp[i][j] = min(dp[i][j], dp[ii][jj] + 1);
	if (dp[l1][l2] != 0x3f3f3f3f) printf("%d\n", dp[l1][l2]);
	else puts("-1");
	return 0;
}
