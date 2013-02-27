#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 30, kMaxM = 30;
int n, m, squ_idx[kMaxN][kMaxM], squ_cnt;
char buf[kMaxN][kMaxM + 1];
int tran[256];
int pos[28][2];
int color[14];
int ans;
char sol[kMaxN][kMaxM + 1];

void Dfs(int squ, int col) {
	if (squ == 14) {
		static bool used[7][7];
		memset(used, false, sizeof(used));
		for (int i = 0; i < 28; ++ i) {
			int a = pos[i][0], b = pos[i][1];
			if (used[color[a]][color[b]]) return;
			used[color[a]][color[b]] = used[color[b]][color[a]] = true;
		}
		++ ans;
		if (ans == 1) {
			for (int i = 0; i < n; ++ i)
				for (int j = 0; j < m; ++ j)
					if (buf[i][j] == '.') sol[i][j] = '.';
					else sol[i][j] = '0' + color[squ_idx[i][j]];
		}
	}
	else {
		if (color[squ] != -1) {
			Dfs(squ + 1, col);
		}
		else {
			int rec = squ + 1;
			for ( ; rec < 14; ++ rec)
				if (color[rec] == -1) {
					color[squ] = color[rec] = col;
					Dfs(squ + 1, col + 1);
					color[squ] = color[rec] = -1;
				}
		}
	}
}

int main() {
	for (int i = 0; i < 26; ++ i) tran['a' + i] = i;
	tran['A'] = 26, tran['B'] = 27;
	scanf("%d%d", &n, &m);
	memset(squ_idx, -1, sizeof(squ_idx));
	memset(pos, -1, sizeof(pos));
	for (int i = 0; i < n; ++ i) {
		scanf("%s", buf[i]);
		for (int j = 0; j < m; ++ j)
			if (buf[i][j] != '.') {
				if (squ_idx[i][j] == -1) {
					squ_idx[i][j] = squ_idx[i][j + 1] = squ_idx[i + 1][j] = squ_idx[i + 1][j + 1] = squ_cnt ++;
				}
				int idx = tran[buf[i][j]];
				if (pos[idx][0] == -1) pos[idx][0] = squ_idx[i][j];
				else pos[idx][1] = squ_idx[i][j];
			}
	}
	memset(color, -1, sizeof(color));
	Dfs(0, 0);
	printf("%d\n", ans * 5040);
	for (int i = 0; i < n; ++ i) printf("%s\n", sol[i]);
	return 0;
}
