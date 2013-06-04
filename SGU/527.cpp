#include <cstdio>

char buf[33];
int msk[33];
int n, m;
int ans;

void Dfs(int step, int cur, int cnt) {
	if (step == n) {
		if (__builtin_popcount(cur) <= cnt)
			ans = (cnt < ans ? cnt : ans);
		return;
	}
	Dfs(step + 1, cur, cnt + 1);
	Dfs(step + 1, cur | msk[step], cnt);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%s", buf);
		for (int j = 0; j < m; ++ j)
			msk[i] |= (buf[j] == '*') << j;
	}
	ans = 33;
	Dfs(0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
