#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kRec[10][8] = {
	{0, 1, 6, 3, 2, 4, -1},
	{2, 3, -1},
	{4, 2, 5, 1, 6, -1},
	{4, 2, 5, 3, 6, -1},
	{0, 5, 2, 3, -1},
	{4, 0, 5, 3, 6, -1},
	{4, 0, 5, 3, 6, 1, -1},
	{4, 2, 3, -1},
	{4, 0, 5, 2, 1, 3, 6, -1},
	{4, 0, 5, 2, 3, 6, -1}
};
const int kMaxN = 100000;
char src[kMaxN * 2 + 1];
int s[kMaxN * 2], cnt[kMaxN + 1], suf[kMaxN + 1], _pre[kMaxN + 1], *pre = _pre + 1;
int n, mask[10], w[10][10];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for (int i = 0; i < 10; ++ i)
		for (int j = 0; kRec[i][j] != -1; ++ j) mask[i] |= 1 << kRec[i][j];
	for (int i = 0; i < 10; ++ i) 
		for (int j = 0; j < 10; ++ j) w[i][j] = __builtin_popcount(mask[i] & mask[j]);
	scanf("%s", src);
	n = strlen(src) / 2;
	reverse(src, src + 2 * n);
	int ori = 0;
	for (int i = 0; i < n; ++ i) {
		s[i] = src[i] - '0';
		s[i + n] = src[i + n] - '0';
		ori += w[s[i]][s[i + n]];
	}
	for (int i = n - 1; i >= 0; -- i) cnt[i] = cnt[i + 1] + w[s[i]][s[i + n]];
	for (int i = 0; i < n; ++ i) pre[i] = pre[i - 1] + w[s[i + n]][s[i + n]];
	for (int i = n - 1; i >= 0; -- i) suf[i] = suf[i + 1] + w[s[i + n]][s[i + n]];
	for (int i = 0; i < 2 * n; ++ i)
		for (int p = s[i] + 1; p < 10; ++ p) {
			int bst = 0;
			if (i < n) 
				bst = cnt[i + 1] + pre[i - 1] + w[p][s[i + n]];
			else 
				bst = 7 * (i - n) + suf[i - n + 1] + w[p][p];
			if (bst <= ori) continue;
			s[i] = p;
			src[i] = p + '0';
			for (int j = 0; j < i; ++ j) s[j] = 8;
			for (int j = i - 1; j >= 0; -- j)
				for (int q = 0; q < 10; ++ q) {
					if (bst - w[s[j]][s[j < n ? j + n : j - n]] + w[q][s[j < n ? j + n : j - n]] > ori) {
						bst = bst - w[s[j]][s[j < n ? j + n : j - n]] + w[q][s[j < n ? j + n : j - n]];
						s[j] = q;
						src[j] = q + '0';
						break;
					}	
				}
			reverse(src, src + 2 * n);
			puts(src);
			return 0;
		}
	puts("-1");
	return 0;
}
