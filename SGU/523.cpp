#include <cstdio>
#include <cstdlib>

const int kMaxN = 100, kMaxF = 100;
int n, cur, e[kMaxN];
bool press[kMaxF];

int main() {
	scanf("%d%d", &n, &cur);
	-- cur;
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &e[i]);
		-- e[i];
		press[e[i]] = true;
	}
	for (int i = 0, fir = 1; i < n; ++ i) {
		if (!press[e[i]]) continue;
		while (cur != e[i]) {
			cur += (e[i] - cur) / abs(e[i] - cur);
			if (press[cur]) {
				if (fir) 
					fir = 0;
				else 
					printf(" ");
				printf("%d", cur + 1);
				press[cur] = false;
			}
		}
	}
	printf("\n");
	return 0;
}
