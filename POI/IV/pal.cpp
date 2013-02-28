/*
 * $File: pal.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given N cities with petrol stations,
 *   and the price of petrol and the distance
 *   between 2 consecutive stations, find minimal
 *   cost to travel throught all roads with
 *   a car with a tank with capacity limit.
 *
 * Solution:
 *   Greedy. Whenever we reach a station, we sell
 *   the petrol that is more expensive than the
 *   price in this city, and fill up the tank. Pay
 *   attention that when we use petrol we should
 *   use the cheapest in the tank.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000;
int p, n, c[kMaxN], d[kMaxN];
int res;
pair<int, int> memo[kMaxN * 2 + 1], *q = memo + kMaxN;
int qh, qt;

int main() {
	scanf("%d%d", &p, &n);
	for (int i = 0; i < n; ++ i)
		scanf("%d%d", &c[i], &d[i]);
	qh = 0, qt = -1;
	q[++ qt] = make_pair(c[0], p);
	for (int i = 1; i <= n; ++ i) {
		int e = d[i - 1];
		while (e) {
			int a = q[qh].first, b = q[qh].second;
			++ qh;
			int f = min(e, b);
			e -= f, b -= f;
			res += f * a;
			if (b) q[-- qh] = make_pair(a, b);
		}
		if (i != n) {
			e = 0;
			while (qh <= qt && q[qt].first >= c[i]) {
				e += q[qt].second;
				-- qt;
			}
			q[++ qt] = make_pair(c[i], e + d[i - 1]);
		}
	}
	printf("%d\n", res);
	return 0;
}
