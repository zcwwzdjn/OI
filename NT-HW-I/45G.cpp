#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 6000;
int n, m, seq[kMaxN + 1];
bool ban[kMaxN + 1];

const int kMaxR = 6000, kMaxP = 783;
bool vis[kMaxR + 1];
int pr[kMaxP + 1];

bool IsPrime(int x) {
	if (x < 2) return false;
	for (int i = 2; i * i <= x; ++ i)
		if (x % i == 0) return false;
	return true;
}

void Init() {
	for (int i = 2; i <= kMaxR; ++ i) {
		if (!vis[i]) pr[++ pr[0]] = i;
		for (int j = 1, k; j <= pr[0] && (k = pr[j] * i) <= kMaxR; ++ j) {
			vis[k] = true;
			if (i % pr[j] == 0) break;
		}
	}
}

void Solve(int x) {
	Init();
	for (int i = 1; i <= pr[0]; ++ i) {
		if (pr[i] > x) break;
		int y = x - pr[i];
		if ((y <= kMaxR && !vis[y]) || (y > kMaxR && IsPrime(y))) {
			for (int j = 1; j <= n; ++ j)
				if (!ban[j]) seq[j] = 1;
			seq[pr[i]] = 2;
			return;
		}
	}
}

int main() {
	scanf("%d", &n);
	m = n * (n + 1) / 2;
	if (IsPrime(m)) {
		for (int i = 1; i <= n; ++ i) seq[i] = 1;
	}
	else if (m & 1) {
		if (IsPrime(m - 2)) {
			for (int i = 1; i <= n; ++ i) seq[i] = 1;
			seq[2] = 2;
		}
		else {
			ban[3] = true;
			seq[3] = 3;
			Solve(m - 3);
		}
	}
	else Solve(m);
	for (int i = 1; i <= n; ++ i) {
		if (i > 1) printf(" ");
		printf("%d", seq[i]);
	}
	puts("");
	return 0;
}
