#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef set<int>::iterator It;
const int kMaxN = 100000, kMaxM = 1000;
int n, m, ori[kMaxN], pos[kMaxM], rec[kMaxM], suc[kMaxN];
map<int, int> idx;
ll val[kMaxN + 1], sum[kMaxN + 1], ans;
bool vis[kMaxM];
set<int> bst;

bool Check(int x) {
	while (x) {
		int y = x % 10;
		if (y != 4 && y != 7) return false;
		x /= 10;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &ori[i]);
		if (Check(ori[i])) {
			if (!idx.count(ori[i])) {
				int t = idx.size();
				idx[ori[i]] = t;
			}
			ori[i] = idx[ori[i]];
			pos[m ++] = i;
		}
		else ori[i] = -1;
	}
	for (int i = 0; i < m; ++ i) rec[i] = n;
	for (int i = n - 1; i >= 0; -- i)
		if (ori[i] != -1) {
			suc[i] = rec[ori[i]];
			rec[ori[i]] = i;
		}
	for (int i = 1; i <= n; ++ i) {
		val[i] = (ll)(i + 1) * i / 2;
		sum[i] = sum[i - 1] + val[i];
	}
	for (int i = 0; i <= m; ++ i) {
		int r = (i < m ? pos[i] : n);
		int l = (i > 0 ? pos[i - 1] : -1);
		for (int j = 1; j <= r - l - 1; ++ j) ans += val[n - l - j - 1] * j;
	}
	for (int i = 0; i < m; ++ i) {
		bst.clear();
		bst.insert(n);
		memset(vis, false, sizeof(vis));
		ll tmp = 0;
		for (int j = i; j >= 0; -- j) {
			if (!vis[ori[pos[j]]]) {
				vis[ori[pos[j]]] = true;
				int p = suc[pos[j]];
				while (p < n) {
					It it = bst.insert(p).first;
					if (it == bst.begin()) {
						++ it;
						tmp += val[*it - p - 1];
					}
					else {
						It prev = it, succ = it;
						-- prev, ++ succ;
						tmp -= val[*succ - *prev - 1];
						tmp += val[*succ - p - 1] + val[p - *prev - 1];
					}
					p = suc[p];
				}
			}
			ll left = pos[j] - (j == 0 ? -1 : pos[j - 1]);
			ans += left * (sum[*bst.begin() - pos[i] - 1] - sum[max(0, *bst.begin() - (i + 1 == m ? n : pos[i + 1]) - 1)]);
			ans += left * (tmp * (min((i + 1 == m ? n : pos[i + 1]), *bst.begin()) - pos[i]));
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
