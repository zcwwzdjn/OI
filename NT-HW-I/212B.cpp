#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000, kMaxM = 10000;
char str[kMaxN + 1];
int n, m, ans[kMaxM];
int next[26][kMaxN], pos[26];
int axis[kMaxM], axis_cnt;
int val[kMaxM], cnt[kMaxM];
short rec[1 << 26];
int req[kMaxM];

int main() {
	scanf("%s%d", str, &m);
	n = strlen(str);
	for (int j = 0; j < 26; ++ j) pos[j] = n;
	for (int i = n - 1; i >= 0; -- i) {
		pos[str[i] - 'a'] = i;
		for (int j = 0; j < 26; ++ j) next[j][i] = pos[j];
	}
	for (int i = 0; i < m; ++ i) { 
		static char buf[32];
		scanf("%s", buf);
		int t = 0;
		for (int j = strlen(buf) - 1; j >= 0; -- j)
			t |= 1 << (buf[j] - 'a');
		req[i] = t;
		axis[axis_cnt ++] = t;
	}
	sort(axis, axis + axis_cnt);
	axis_cnt = unique(axis, axis + axis_cnt) - axis;
	for (int i = 0; i < 1 << 26; ++ i) rec[i] = axis_cnt;
	for (int i = 0; i < axis_cnt; ++ i) rec[axis[i]] = i;
	for (int i = 0; i < n; ++ i) {
		int mask = 1 << (str[i] - 'a');
		int j = i;
		while (true) {
			int now = ((1 << 26) - 1) ^ mask;
			int nxt = n;
			while (now) {
				int p = now & -now;
				now ^= p;
				p = __builtin_ctz(p);
				nxt = min(nxt, next[p][j]);
			}
			if (rec[mask] != axis_cnt) {
				int t = rec[mask];
				if (nxt > val[t]) {
					val[t] = nxt;
					++ cnt[t];
				}
			}
			if (nxt == n) break;
			j = nxt;
			mask |= 1 << (str[j] - 'a');
		}
	}
	for (int i = 0; i < m; ++ i) {
		int mask = req[i];
		printf("%d\n", cnt[rec[mask]]);
	}
	return 0;
}
