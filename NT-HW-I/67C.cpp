#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 4000, kInf = 0x3f3f3f3f;
int ti, td, tr, te;
int na, nb, dp[kMaxN + 1][kMaxN + 1];
char a[kMaxN + 2], b[kMaxN + 2];
int nextb[kMaxN + 1][26], pos[26];
int nexta[kMaxN + 1][26];

void Min(int &des, int src) {
	des = min(des, src);
}

int Check(int l1, int r1, int l2, int r2) {
	int s1 = r1 - l1 - 1, s2 = r2 - l2 - 1;
	return (td * s1 + ti * s2);
}

int main() {
	scanf("%d%d%d%d%s%s", &ti, &td, &tr, &te, a + 1, b + 1);
	na = strlen(a + 1), nb = strlen(b + 1);
	tr = min(tr, ti + td);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < 26; ++ i) pos[i] = nb + 1;
	for (int i = nb; i >= 1; -- i) {
		for (int j = 0; j < 26; ++ j) nextb[i][j] = pos[j];
		pos[b[i] - 'a'] = i;
	}
	for (int i = 0; i < 26; ++ i) pos[i] = na + 1;
	for (int i = na; i >= 1; -- i) {
		for (int j = 0; j < 26; ++ j) nexta[i][j] = pos[j];
		pos[a[i] - 'a'] = i;
	}
	for (int i = 0; i <= na; ++ i)
		for (int j = 0; j <= nb; ++ j)
			if (dp[i][j] < kInf && (i < na || j < nb)) {
				if (i == na) Min(dp[i][j + 1], dp[i][j] + ti);
				else if (j == nb) Min(dp[i + 1][j], dp[i][j] + td);
				else {
					Min(dp[i + 1][j + 1], dp[i][j] + (a[i + 1] != b[j + 1] ? tr : 0));
					Min(dp[i][j + 1], dp[i][j] + ti);
					Min(dp[i + 1][j], dp[i][j] + td);
					if (i + 2 <= na && j + 2 <= nb) {
						Min(dp[i + 2][j + 2], dp[i][j] + te + (a[i + 1] != b[j + 2] ? tr : 0) + (a[i + 2] != b[j + 1] ? tr : 0));
						if (nextb[j + 1][a[i + 1] - 'a'] <= nb) {
							Min(dp[i + 2][nextb[j + 1][a[i + 1] - 'a']], dp[i][j] + te + (a[i + 2] != b[j + 1] ? tr : 0) + ti * (nextb[j + 1][a[i + 1] - 'a'] - (j + 2))); 
						}
						if (nexta[i + 1][b[j + 1] - 'a'] <= na) {
							Min(dp[nexta[i + 1][b[j + 1] - 'a']][j + 2], dp[i][j] + te + (a[i + 1] != b[j + 2] ? tr : 0) + td * (nexta[i + 1][b[j + 1] - 'a'] - (i + 2)));
						}	
						if (nextb[j + 1][a[i + 1] - 'a'] <= nb && nexta[i + 1][b[j + 1] - 'a'] <= na) {
							Min(dp[nexta[i + 1][b[j + 1] - 'a']][nextb[j + 1][a[i + 1] - 'a']], dp[i][j] + te + Check(i + 1, nexta[i + 1][b[j + 1] - 'a'], j + 1, nextb[j + 1][a[i + 1] - 'a']));
						}
					}	
				}
			}
	printf("%d\n", dp[na][nb]);
	return 0;
}
