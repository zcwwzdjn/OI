#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

#define FIRST 0
#define SECOND 1
#define TIE 2

map<pair<int, int>, int> memo;
int a, b, n;
stack<pair<pair<int, int>, pair<int, int> > > s;

long long Pow(int a, int b) {
	long long res = 1, tmp = a;
	while (b) {
		if (b & 1) res *= tmp;
		b >>= 1;
		tmp *= tmp;
	}
	return res;
}

int Dfs(int a, int b) {
	if (memo.count(make_pair(a, b))) return memo[make_pair(a, b)];
	int &res = memo[make_pair(a, b)];
	if (Pow(a, b) >= n) return (res = FIRST);
	if (Pow(a + 1, b) >= n && a == 1) return (res = TIE);
	if (b == 1 && (long long)a * a >= n) return (res = (n - a) % 2);
	if (Dfs(a + 1, b) == FIRST && Dfs(a, b + 1) == FIRST) return (res = SECOND);
	else return (res = FIRST);
}

#define mp make_pair

void Dfs() {
	s.push(mp(mp(a, b), mp(0, 0)));
	while (s.size()) {
		pair<int, int> tmp = s.top().first;
		int a = tmp.first, b = tmp.second;
		if (Pow(a, b) >= n) {
			memo[tmp] = FIRST;
			s.pop();
		}
		else if (Pow(a + 1, b) >= n && a == 1) {
			memo[tmp] = TIE;
			s.pop();
		}
		else if (b == 1 && (long long)a * a >= n) {
			memo[tmp] = (n - a) % 2;
			s.pop();
		}
		else {
			int &cnt = s.top().second.first, &pos = s.top().second.second;
			if (pos == 0) {
				if (memo.count(mp(a + 1, b))) cnt += (memo[mp(a + 1, b)] == FIRST), ++ pos;
				else {
					s.push(mp(mp(a + 1, b), mp(0, 0)));
					continue;
				}
			}
			else if (pos == 1) {
				if (memo.count(mp(a, b + 1))) cnt += (memo[mp(a, b + 1)] == FIRST), ++ pos;
				else {
					s.push(mp(mp(a, b + 1), mp(0, 0)));
					continue;
				}
			}
			else {
				if (cnt == 2) memo[tmp] = SECOND;
				else memo[tmp] = FIRST;
				s.pop();
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &a, &b, &n);
	Dfs();
	int res = memo[mp(a, b)];
	if (res == SECOND) puts("Stas");
	else if (res == TIE) puts("Missing");
	else puts("Masha");
	return 0;
}
