#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int kMaxM = 120, kMod = 1000000007;
int m, t, cnt[kMaxM];
int ans;

struct Int128 {
	ull bit[2];
	Int128() {}
	Int128(ull a_, ull b_) {
		bit[0] = a_, bit[1] = b_;
	}
} hash;

Int128 operator | (const Int128 &a, const Int128 &b) {
	return Int128(a.bit[0] | b.bit[0], a.bit[1] | b.bit[1]);
}

Int128 LeftShift(const Int128 &a, int d) {
	ull t = 0;
	if (m <= 64) {
		t = a.bit[0] >> (m - d);
	}
	else {
		if (m - d >= 64) t = a.bit[1] >> (m - 64 - d);
		else t = a.bit[1] << (d - (m - 64)) | a.bit[0] >> (m - d);
	}
	Int128 res(0, 0);
	if (m <= 64) {
		res.bit[0] = a.bit[0] & ((1LL << (m - d)) - 1);
		res.bit[0] <<= d;
		res.bit[0] |= t;
	}
	else {
		if (m - d >= 64) {
			res.bit[1] = a.bit[1] & ((1LL << (m - 64 - d)) - 1);
			res.bit[1] <<= d;
			res.bit[1] |= a.bit[0] >> (64 - d);
			res.bit[0] = a.bit[0] & ((1LL << (64 - d)) - 1);
			res.bit[0] <<= d;
			res.bit[0] |= t;
		}
		else {
			res.bit[1] = a.bit[0] & ((1LL << (m - d)) - 1);
			res.bit[0] = res.bit[1] & ((1LL << (64 - d)) - 1);
			res.bit[1] >>= (64 - d);
			res.bit[0] <<= d;
			res.bit[0] |= t;
		}
	}
	return res;
}

ull Swap(ull x) {
	x = (x & 0x5555555555555555LL) << 1 | (x & 0xAAAAAAAAAAAAAAAALL) >> 1;
	x = (x & 0x3333333333333333LL) << 2 | (x & 0xCCCCCCCCCCCCCCCCLL) >> 2;
	x = (x & 0x0f0f0f0f0f0f0f0fLL) << 4 | (x & 0xf0f0f0f0f0f0f0f0LL) >> 4;
	x = (x & 0x00ff00ff00ff00ffLL) << 8 | (x & 0xff00ff00ff00ff00LL) >> 8;
	x = (x & 0x0000ffff0000ffffLL) << 16 | (x & 0xffff0000ffff0000LL) >> 16;
	x = (x & 0x00000000ffffffffLL) << 32 | (x & 0xffffffff00000000LL) >> 32;
	return x;
}

Int128 Reverse(const Int128 &a) {
	Int128 res(0, 0);
	if (m <= 64) {
		res.bit[0] = Swap(a.bit[0]);
		res.bit[0] >>= (64 - m);
	}
	else {
		res.bit[1] = a.bit[0] & ((1LL << (m - 64)) - 1);
		res.bit[0] = a.bit[1] << (128 - m) | a.bit[0] >> (m - 64);
		res.bit[0] = Swap(res.bit[0]);
		res.bit[1] = Swap(res.bit[1]);
		res.bit[1] >>= (128 - m);
	}
	return res;
}

Int128 RightShift(const Int128 &a, int d) {
	return Reverse(LeftShift(Reverse(a), d));
}

void Dfs(int step, int last, int cur) {
	ans = (ans + cur) % kMod;
	if (step < 6) {
		for (int i = last + 1; i < m; ++ i)
			if (cnt[i] && !(hash.bit[0] >> i & 1)) {
				Int128 rec = hash;
				hash = hash | (LeftShift(hash, i) | RightShift(hash, i));
				Dfs(step + 1, i, (long long)cur * cnt[i] % kMod);
				hash = rec;
			}
	}
}

int main() {
	scanf("%*d%d%d", &m, &t);
	for (int x; t --; ) {
		scanf("%d", &x);
		x %= m;
		++ cnt[min(x, m - x)];
	}
	hash.bit[0] = 1;
	Dfs(0, 0, 1);
	printf("%d\n", ans);
	return 0;
}
