#include <cstdio>
#include <cstring>

const int kMaxN = 200, kMaxK = 200;
int n, g[kMaxN][kMaxN], k, r[kMaxK];
bool reach[2][kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			scanf("%d", &g[i][j]);
	scanf("%d", &k);
	for (int i = 0; i < k; ++ i)
		scanf("%d", &r[i]);
	int des = 0, src = 1;
	reach[des][0] = true;
	for (int i = 0; i < k; ++ i) {
		des ^= 1, src ^= 1;
		memset(reach[des], false, sizeof(reach[des]));
		for (int u = 0; u < n; ++ u)
			if (reach[src][u])
				for (int v = 0; v < n; ++ v)
					if (g[u][v] == r[i])
						reach[des][v] = true;
	}
	int cnt = 0;
	for (int i = 0; i < n; ++ i)
		cnt += reach[des][i];
	printf("%d\n", cnt);
	if (cnt) {
		for (int i = 0, fir = 1; i < n; ++ i)
			if (reach[des][i]) {
				if (fir)
					fir = 0;
				else
					printf(" ");
				printf("%d", i + 1);
			}
		printf("\n");
	}
	return 0;
}
