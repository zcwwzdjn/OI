#include <cstdio>
#include <cstring>

typedef long long ll;
char buf[111111];
char pat[111];
int n, m;
int next[111111][26];
int pos[26];

int main() {
	scanf("%s%s", buf, pat);
	n = strlen(buf);
	m = strlen(pat);
	for (int j = 0; j < 26; ++ j) pos[j] = n, next[n][j] = n;
	for (int i = n - 1; i >= 0; -- i) {
		pos[buf[i] - 'a'] = i;
		for (int j = 0; j < 26; ++ j) next[i][j] = pos[j];
	}
	ll res = 0;
	for (int i = 0, j, k; i < n; ++ i) {
		for (j = i - 1, k = 0; k < m && j != n; ++ k)
			j = next[j + 1][pat[k] - 'a'];
		res += n - j;
	}
#ifdef unix
	printf("%lld\n", res);
#else
	printf("%I64d\n", res);
#endif
	return 0;
}
