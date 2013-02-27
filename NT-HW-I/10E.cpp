#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 400;
int n, seq[kMaxN];
int cnt[kMaxN], ppp[kMaxN];

int Check(int v, int i, int *arr) {
	int res = 0;
	memset(arr, 0, sizeof(int) * n);
	for ( ; i < n; ++ i) {
		res += (arr[i] = v / seq[i]);
		v %= seq[i];
	}
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < n - 1; ++ i) {
		Check(seq[i] - 1, i + 1, cnt);
		for (int j = i + 1; j < n; ++ j) {
			int tmp = seq[j], tot = 1;
			for (int k = i + 1; k <= j; ++ k) {
				tot += cnt[k];
				tmp += seq[k] * cnt[k];
			}
			if (tmp > seq[i]) {
				int orz = Check(tmp, 0, ppp);
				if (orz > tot) ans = min(ans, tmp);
			}
		}
	}
	if (ans == 0x3f3f3f3f) puts("-1");
	else printf("%d\n", ans);
	return 0;
}
