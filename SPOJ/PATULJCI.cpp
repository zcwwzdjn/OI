#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 300000, kMaxC = 100000;
int n, c, seq[kMaxN];
int lb[kMaxC], rb[kMaxC];
int m;
int memo[17][kMaxN + 1], *cnt[17];

struct Node {
	int val, pos;
	bool operator < (const Node &t) const {
		return (val != t.val ? val < t.val : pos < t.pos);
	}
} node[kMaxN];

int main() {
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &seq[i]), -- seq[i];
		node[i].val = seq[i], node[i].pos = i;
	}
	sort(node, node + n);
	memset(lb, -1, sizeof(lb));
	memset(rb, -1, sizeof(rb));
	for (int i = 0; i < n; ++ i) {
		if (lb[node[i].val] == -1) lb[node[i].val] = i;
		rb[node[i].val] = i;
	}
	scanf("%d", &m);
	for (int i = 0; i < 17; ++ i) cnt[i] = memo[i] + 1;
	for (int j = 0; j < 17; ++ j) 
		for (int i = 0; i < n; ++ i) {
			cnt[j][i] = cnt[j][i - 1];
			if (seq[i] >> j & 1) ++ cnt[j][i];
		}
	for (int l, r; m --; ) {
		scanf("%d%d", &l, &r);
		-- l, -- r;
		int k = (r - l + 1) / 2, res = 0;
		for (int j = 0; j < 17; ++ j)
			if (cnt[j][r] - cnt[j][l - 1] > k) res |= 1 << j;
		if (res >= c || lb[res] == -1) res = -1;
		else {
			int st = lb[res] - 1, ed = rb[res];
			while (st + 1 < ed) {
				int mid = (st + ed) >> 1;
				if (node[mid].pos < l) st = mid;
				else ed = mid;
			}
			l = ed;
			st = lb[res], ed = rb[res] + 1;
			while (st + 1 < ed) {
				int mid = (st + ed) >> 1;
				if (node[mid].pos > r) ed = mid;
				else st = mid;
			}
			r = st;
			if (r - l + 1 <= k) res = -1;
		}
		if (res == -1) puts("no");
		else printf("yes %d\n", res + 1);
	}
	return 0;
}
