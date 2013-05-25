#include <climits>
#include <cstdio>
#include <algorithm>

using std::min;

int m;

int main() {
	scanf("%d", &m);
	if (m == 21)
		printf("1\n");
	else {
		int res = INT_MAX;
		for (int up = 1; up <= 6; ++ up)
			for (int lo = 1; lo <= 6; ++ lo) {
				int n = m - (21 - up) - (21 - lo);
				if (n >= 0 && n % 14 == 0)
					res = min(res, n / 14 + 2);
			}
		if (res == INT_MAX)
			printf("-1\n");
		else
			printf("%d\n", res);	
	}
	return 0;
}
