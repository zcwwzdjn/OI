#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

#define mp make_pair

int n, v[20];
vector<pair<int, int> > sol;

void Solve2(int cur, int a, int b, int c) {
	int nxt = cur;
	while (nxt < n && v[nxt] == v[cur]) ++ nxt;
	if (nxt == n) {
		for (int i = cur; i < nxt; ++ i) sol.push_back(mp(a, c));
	}
	else {
		Solve2(nxt, a, c, b);
		for (int i = cur; i < nxt; ++ i) sol.push_back(mp(a, c));
		Solve2(nxt, b, a, c);
	}
}

void Solve(int cur, int a, int b, int c) {
	int nxt = cur;
	while (nxt < n && v[nxt] == v[cur]) ++ nxt;
	if (nxt == n) {
		for (int i = cur; i < nxt - 1; ++ i) sol.push_back(mp(a, b));
		sol.push_back(mp(a, c));
		for (int i = cur; i < nxt - 1; ++ i) sol.push_back(mp(b, c));
	}
	else if (nxt - cur == 1) Solve2(cur, a, b, c);
	else {
		Solve2(nxt, a, b, c);
		for (int i = cur; i < nxt; ++ i) sol.push_back(mp(a, b));
		Solve2(nxt, c, b, a);
		for (int i = cur; i < nxt; ++ i) sol.push_back(mp(b, c));
		Solve(nxt, a, b, c);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &v[i]);
	Solve(0, 0, 1, 2);
	printf("%d\n", sol.size());
	for (int i = 0; i < (int)sol.size(); ++ i)
		printf("%d %d\n", sol[i].first + 1, sol[i].second + 1);
	return 0;
}
