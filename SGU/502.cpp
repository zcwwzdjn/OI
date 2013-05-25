#include <cstdio>

#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

typedef long long LL;
LL num;
int len, digit_cnt[10];

bool Dfs(int dep, LL cur) {
	if (dep == len) {
		if (cur % 17 == 0) {
			printf(LL_FMT "\n", cur);
			return true;
		}
		return false;
	}
	for (int d = (dep == 0); d < 10; ++ d)
		if (digit_cnt[d]) {
			digit_cnt[d] -= 1;
			if (Dfs(dep + 1, cur * 10 + d))
				return true;
			digit_cnt[d] += 1;
		}
	return false;
}

int main() {
	scanf(LL_FMT, &num);
	while (num) {
		digit_cnt[num % 10] += 1;
		num /= 10;
		len += 1;
	}
	if (!Dfs(0, 0LL))
		printf("-1\n");
	return 0;
}
