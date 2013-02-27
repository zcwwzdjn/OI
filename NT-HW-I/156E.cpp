#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 10000, kMaxM = 30000, kMaxBase = 16, kMaxLen = 30;
const int kPr[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
const int kMod[5] = {223092870, 58642669, 600662303, 33984931, 8633};
map<int, int> dp[kMaxBase + 1][5];
int idx[256], len[kMaxBase + 1];
int n, m;

int Hash(int src, int base) {
	static int seq[32];
	int idx = 0;
	do {
		seq[idx ++] = src % base;
		src /= base;
	} while (src);
	reverse(seq, seq + idx);
	int res = 0;
	for (int i = 0; i < idx; ++ i) res = res * (base + 1) + seq[i];
	return res;
}

int Hash(char *src, int base) {
	static int seq[32];
	int idx = 0;
	::idx['?'] = base;
	while (*src) {
		seq[idx ++] = ::idx[*src];
		++ src;
	}
	int res = 0;
	for (int i = 0; i < idx; ++ i) res = res * (base + 1) + seq[i];
	return res;
}	

int Calc(int base, int mod, int mask) {
	if (dp[base][mod].count(mask)) return dp[base][mod][mask];
	int now = mask, p = 1;
	int &res = dp[base][mod][mask];
	res = -1;
	while (now) {
		int t = now % (base + 1);
		now /= (base + 1);
		if (t == base) {
			for (int i = 0; i < base; ++ i) {
				int tmp = mask + (i - base) * p;
				tmp = Calc(base, mod, tmp);
				if (tmp != -1) {
					if (res == -1) res = 1;
					res = (long long)res * tmp % kMod[mod];
				}
			}
			break;
		}
		p *= (base + 1);
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	for (int i = 0; i < 10; ++ i) idx[i + '0'] = i;
	for (int i = 10; i < 16; ++ i) idx[i - 10 + 'A'] = i;
	scanf("%d", &n);
	for (int i = 2; i <= 16; ++ i) {
		int tmp = 1;
		for (int j = 1; j <= kMaxLen; ++ j) {
			tmp *= i;
			if (tmp >= n) {
				len[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		ll x;
		scanf("%I64d", &x);
		for (int j = 2; j <= 16; ++ j) {
			int tmp = Hash(i, j);
			for (int k = 0; k < 5; ++ k)
				dp[j][k][tmp] = x % kMod[k];
		}
	}
	for (scanf("%d", &m); m --; ) {
		int b;
		ll c;
		static char buf[32];
		scanf("%d%s%I64d", &b, buf, &c);
		int sz = strlen(buf);
		int ans = 100;
		if (sz > len[b]) {
			bool fail = false;
			int delta = sz - len[b];
			for (int i = 0; i < delta; ++ i) {
				if (buf[i] != '?' && buf[i] != '0') {
					fail = true;
					break;
				}
				buf[i] = '0';
			}
			if (fail) {
				for (int i = 0; i < 25; ++ i)
					if (c % kPr[i] == 0) {
						ans = kPr[i];
						break;
					}
				if (ans == 100) puts("-1");
				else printf("%d\n", ans);
				continue;
			}
		}
		int hash = Hash(buf, b);
		for (int i = 0; i < 5 && ans == 100; ++ i) {
			int tmp = Calc(b, i, hash);
			if (tmp == -1) tmp = 1;
			for (int j = 0; j < 25 && ans == 100; ++ j)
				if (kMod[i] % kPr[j] == 0) {
					int o = tmp % kPr[j];
					o = (o + c % kPr[j]) % kPr[j];
					if (o == 0) ans = min(ans, kPr[j]);
				}
		}
		if (ans != 100) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
}
