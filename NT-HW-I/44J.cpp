#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kFx[2] = {0, 1}, kFy[2] = {1, 0};
const int kMaxN = 1000, kMaxM = 1000;
int n, m;
char buf[kMaxN][kMaxM + 1];

bool Have(int x, int y, int d) {
	
	for (int t = 0; t < 3; ++ t) {
		int xx = x + t * kFx[d], yy = y + t * kFy[d];
		if (xx >= 0 && xx < n && yy >= 0 && yy < m && buf[xx][yy] == ((t & 1) ? 'b' : 'w')) continue;
		return false;
	}
	return true;
}

void Paint(int x, int y, int d) {
	int xx = x + kFx[d] * 2, yy = y + kFy[d] * 2;
	bool vis[4];
	memset(vis, false, sizeof(vis));
	for (int i = x - 1; i <= xx + 1; ++ i)
		for (int j = y - 1; j <= yy + 1; ++ j)
			if (i >= 0 && i < n && j >= 0 && j < m && buf[i][j] >= 'c' && buf[i][j] <= 'f') vis[buf[i][j] - 'c'] = true;
	for (int t = 0; t < 4; ++ t)
		if (!vis[t]) {
			for (int i = x; i <= xx; ++ i)
				for (int j = y; j <= yy; ++ j)
					buf[i][j] = 'c' + t;
			return;
		}
}

bool Check() {
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			if (buf[i][j] == 'b') return false;
			if (buf[i][j] != 'w') continue;
			if (!Have(i, j, 0) && !Have(i, j, 1)) return false;
			if (Have(i, j, 0))
				Paint(i, j, 0);
			else
				Paint(i, j, 1);
		}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) scanf("%s", buf[i]);
	if (!Check()) puts("NO");
	else {
		puts("YES");
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j)
				if (buf[i][j] >= 'c' && buf[i][j] <= 'f') buf[i][j] -= 2;
			puts(buf[i]);
		}
	}
	return 0;
}
