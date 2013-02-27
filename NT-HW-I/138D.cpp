#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int kMaxN = 20, kMaxM = 20, kMaxT = kMaxN + kMaxM - 1;
int n, m, t;
char buf[kMaxN][kMaxM + 1], rec[kMaxT][kMaxT];
int pos[kMaxN][kMaxM][2];

int Dfs(int x0, int y0, int x1, int y1, int o) {
	if (x0 > x1 || y0 > y1) return 0;
	static int memo[kMaxT][kMaxT][kMaxT][kMaxT][2];
	static bool done[kMaxT][kMaxT][kMaxT][kMaxT][2];
	if (done[x0][y0][x1][y1][o]) return memo[x0][y0][x1][y1][o];
	done[x0][y0][x1][y1][o] = true;
	set<int> s;
	for (int i = x0; i <= x1; ++ i)
		for (int j = y0; j <= y1; ++ j) if ((j & 1) == o) {
			if (rec[i][j] == 'L') {
				s.insert(Dfs(x0, y0, i - 1, y1, o) ^ Dfs(i + 1, y0, x1, y1, o));
			}
			else if (rec[i][j] == 'R') {
				s.insert(Dfs(x0, y0, x1, j - 1, o) ^ Dfs(x0, j + 1, x1, y1, o));
			}
			else if (rec[i][j] == 'X') {
				s.insert(Dfs(x0, y0, i - 1, j - 1, o) ^ Dfs(x0, j + 1, i - 1, y1, o) ^ Dfs(i + 1, y0, x1, j - 1, o) ^ Dfs(i + 1, j + 1, x1, y1, o));
			}	
		}
	int &res = memo[x0][y0][x1][y1][o];
	res = 0;
	while (s.count(res)) ++ res;
	return res;
	
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) scanf("%s", buf[i]);
	t = n + m - 1;
	if (t == 0) {
		puts("WIN");
		return 0;
	}
	pos[0][0][0] = 0;
	pos[0][0][1] = n - 1;
	for (int i = 1; i < n; ++ i) {
		pos[i][0][0] = pos[i - 1][0][0] + 1;
		pos[i][0][1] = pos[i - 1][0][1] - 1;
	}
	for (int j = 1; j < m; ++ j) {
		pos[0][j][0] = pos[0][j - 1][0] + 1;
		pos[0][j][1] = pos[0][j - 1][1] + 1;
	}
	for (int i = 1; i < n; ++ i)
		for (int j = 1; j < m; ++ j) {
			pos[i][j][0] = pos[i - 1][j][0] + 1;
			pos[i][j][1] = pos[i][j - 1][1] + 1;
		}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j)
			rec[pos[i][j][0]][pos[i][j][1]] = buf[i][j];
	puts((Dfs(0, 0, t - 1, t - 1, 0) ^ Dfs(0, 0, t - 1, t - 1, 1)) ? "WIN" : "LOSE");
	return 0;
}
