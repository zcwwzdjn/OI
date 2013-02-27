#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 50;
int n;
bool odd;
ll k, dp[2][2][2][2][3];

bool Check(int eq, int req, int lu, int ru, int a, int b, int oa, int ob) {
	if (eq && a > b) return false;
	if (req && a > (b ^ 1)) return false;
	if (lu && a > oa) return false;
	return true;
}

void Refresh(int eq, int req, int lu, int ru, int a, int b, int oa, int ob, int &neq, int &nreq, int &nlu, int &nru) {
	if (eq && (a == b)) neq = 1; else neq = 0;
	if (req && (a == (b ^ 1))) nreq = 1; else nreq = 0;
	if (lu && (a == oa)) nlu = 1; else nlu = 0;
	if (b > ob) nru = 2;
	else if (b < ob) nru = 0;
	else nru = ru;
}

ll Calc(ll lim) {
	static int buf[64];
	memset(buf, 0, sizeof(buf));
	for (int i = n - 1; i >= 0; -- i) buf[n - 1 - i] = (int)(lim >> i & 1);
	int m = n / 2;
	int des = 0, src = 1;
	memset(dp[des], 0, sizeof(dp[des]));
	dp[des][1][1][1][1] = 1;
	for (int i = 0; i < m; ++ i) {
		des ^= 1, src ^= 1;
		memset(dp[des], 0, sizeof(dp[des]));
		for (int eq = 0; eq < 2; ++ eq)
			for (int req = 0; req < 2; ++ req)
				for (int lu = 0; lu < 2; ++ lu)
					for (int ru = 0; ru < 3; ++ ru)
						if (dp[src][eq][req][lu][ru])
							for (int a = 0; a < 2; ++ a) if (a == 0 || (a == 1 && i != 0))
								for (int b = 0; b < 2; ++ b) {
									if (a != b && odd && i + 1 == m) continue;
									if (Check(eq, req, lu, ru, a, b, buf[i], buf[n - 1 - i])) {
										int neq, nreq, nlu, nru;
										Refresh(eq, req, lu, ru, a, b, buf[i], buf[n - 1 - i], neq, nreq, nlu, nru);
										dp[des][neq][nreq][nlu][nru] += dp[src][eq][req][lu][ru];
									}
								}
	}
	ll res = 0;
	for (int eq = 0; eq < 2; ++ eq)
		for (int req = 0; req < 2; ++ req)
			res += dp[des][eq][req][0][0] + dp[des][eq][req][0][1] + dp[des][eq][req][0][2] + dp[des][eq][req][1][0] + dp[des][eq][req][1][1];
	return res;
}

bool E(ll t) {
	ll v = 0;
	for (int i = 0; i < n; ++ i)
		v = v << 1 | (t >> i & 1);
	if (v < t) return false;
	ll q = (1LL << n) - 1;
	if ((q ^ t) < t) return false;
	if ((q ^ v) < t) return false;
	if (odd) {	
		int a = (t >> (n / 2)) & 1;
		int b = (v >> (n / 2)) & 1;
		if (a != b) return false;
	}
	return true;
}

int main() {
	scanf("%d%I64d", &n, &k);
	++ k;
	if (n & 1) {
		odd = true;
		++ n;
	}
	ll lb = 0, rb = 1LL << n;
	while (lb + 1 < rb) {
		ll mid = (lb + rb) >> 1;
		ll tmp = Calc(mid);
		if (tmp > k || (tmp == k && !E(mid))) rb = mid;
		else lb = mid;
	}
	if (Calc(lb) == k && lb != ((1LL << n) - 1)) {
		if (odd) lb = lb >> (n / 2) << (n / 2 - 1) | (lb & ((1 << (n / 2)) - 1)), -- n;
		for (int i = n - 1; i >= 0; -- i) printf("%d", (int)(lb >> i & 1));
		puts("");
	}
	else puts("-1");
	return 0;
}
