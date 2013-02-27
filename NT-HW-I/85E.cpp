#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 5000, kMod = 1000000007;
int n, x[kMaxN], y[kMaxN], col[kMaxN], f[kMaxN][kMaxN];
int cnt, dis;
bool fail = false;

void Dfs(int u, int c) {
	if (fail) return;
	col[u] = c;
	for (int v = 0; v < n && !fail; ++ v)
		if (f[u][v] > dis) {
			if (col[v] == c) {
				fail = true;
				break;
			}
			else if (col[v] == -1) {
				Dfs(v, 1 - c);
			}
		}
}

bool Check(int lim) {
	for (int i = 0; i < n; ++ i) col[i] = -1;
	cnt = 0, dis = lim;
	for (int i = 0; i < n; ++ i)
		if (col[i] == -1) {
		   	++ cnt;
			fail = false;
			Dfs(i, 0);
	   		if (fail) return false;
		}
	return true;
}

int PowerMod(int b) {
	int res = 1, tmp = 2;
	while (b) {
		if (b & 1) res = (long long)res * tmp % kMod;
		b >>= 1;
		tmp = (long long)tmp * tmp % kMod;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &x[i], &y[i]);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j) f[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
	int lb = -1, rb = 10000;
	while (lb + 1 < rb) {
		int mid = (lb + rb) >> 1;
		if (Check(mid)) rb = mid;
		else lb = mid;
	}
	printf("%d\n", rb);	
	Check(rb);
	printf("%d\n", PowerMod(cnt));
	return 0;
}
