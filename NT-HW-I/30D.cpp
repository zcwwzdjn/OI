#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, k, x, y, s[kMaxN];
double ans;

double Dist(int xx, int yy) {
	int dx = x - xx, dy = y - yy;
	return sqrt((long long)dx * dx + (long long)dy * dy);
}

int main() {
	scanf("%d%d", &n, &k);
	-- k;
	for (int i = 0; i < n; ++ i) scanf("%d", &s[i]);
	scanf("%d%d", &x, &y);
	if (k == n) {
		sort(s, s + n);
		ans = min(Dist(s[0], 0), Dist(s[n - 1], 0)) + s[n - 1] - s[0];
	}
	else {
		k = s[k];
		sort(s, s + n);
		ans = min(Dist(s[0], 0) + abs(k - s[n - 1]), Dist(s[n - 1], 0) + abs(k - s[0])) + abs(s[n - 1] - s[0]);
		for (int i = 0; i < n; ++ i) {
			// left
			if (i < n - 1)
				ans = min(ans, min(abs(s[i] - k) + Dist(s[0], 0), abs(s[0] - k) + Dist(s[i], 0)) + abs(s[i] - s[0]) +
						min(Dist(s[i + 1], 0), Dist(s[n - 1], 0)) + abs(s[n - 1] - s[i + 1]));
			// right
			if (i > 0)
				ans = min(ans, min(abs(s[i] - k) + Dist(s[n - 1], 0), abs(s[n - 1] - k) + Dist(s[i], 0)) + abs(s[i] - s[n - 1]) +
						min(Dist(s[i - 1], 0), Dist(s[0], 0)) + abs(s[i - 1] - s[0]));
		}
	}
	printf("%.9lf\n", ans);
	return 0;
}
