#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 600;
int n;
int hor_cnt, ver_cnt;

struct Seg {
	int l, r, h;
} hor[kMaxN], ver[kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (y1 == y2) {
			hor[hor_cnt].l = min(x1, x2);
			hor[hor_cnt].r = max(x1, x2);
			hor[hor_cnt ++].h = y1;
		}
		else {
			ver[ver_cnt].l = min(y1, y2);
			ver[ver_cnt].r = max(y1, y2);
			ver[ver_cnt ++].h = x1;
		}
	}
	long long res = 0;
	for (int i = 0; i < ver_cnt - 1; ++ i)
		for (int j = i + 1; j < ver_cnt; ++ j)
			if (ver[i].h != ver[j].h) {
				int cnt = 0;
				int lb = min(ver[i].h, ver[j].h);
				int rb = max(ver[i].h, ver[j].h);
				for (int k = 0; k < hor_cnt; ++ k)
					if (hor[k].l <= lb && hor[k].r >= rb && hor[k].h >= ver[i].l && hor[k].h <= ver[i].r && hor[k].h >= ver[j].l && hor[k].h <= ver[j].r)
						++ cnt;
				res += (long long)cnt * (cnt - 1) / 2;
			}
#ifdef unix
	printf("%lld\n", res);
#else
	printf("%I64d\n", res);
#endif
	return 0;
}
