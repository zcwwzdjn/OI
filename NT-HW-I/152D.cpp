#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000, kMaxM = 1000;
int n, m;
char buf[kMaxN + 1][kMaxM + 2];
int row[kMaxN + 1][kMaxM + 1], col[kMaxN + 1][kMaxM + 1];
int dr[kMaxN + 1][kMaxM + 1], dc[kMaxN + 1][kMaxM + 1];
int r[kMaxN + 1], c[kMaxM + 1];
int rr[kMaxN + 1], cc[kMaxM + 1];
int sum;

#define PY puts("YES")
#define PN puts("NO")

bool C(int x0, int y0, int x1, int y1) {
	if (x1 - x0 + 1 < 3) return false;
	if (y1 - y0 + 1 < 3) return false;
	int a = x1 - x0 + 1, b = y1 - y0 + 1;
	return (row[x0][y1] - row[x0][y0 - 1] == b &&
			row[x1][y1] - row[x1][y0 - 1] == b &&
			col[x1][y0] - col[x0 - 1][y0] == a &&
			col[x1][y1] - col[x0 - 1][y1] == a
		   );
}

void D(int x0, int y0, int x1, int y1) {
	for (int i = y0; i <= y1; ++ i) {
		if (buf[x0][i] == '#') {
			-- sum;
			buf[x0][i] = '.';
		}
		if (buf[x1][i] == '#') {
			-- sum;
			buf[x1][i] = '.';
		}
	}
	for (int i = x0; i <= x1; ++ i) {
		if (buf[i][y0] == '#') {
			-- sum;
			buf[i][y0] = '.';
		}
		if (buf[i][y1] == '#') {
			-- sum;
			buf[i][y1] = '.';
		}
	}
}

void E(int x0, int y0, int x1, int y1) {
	for (int i = y0; i <= y1; ++ i) {
		if (buf[x0][i] != '#') {
			++ sum;
			buf[x0][i] = '#';
		}
		if (buf[x1][i] != '#') {
			++ sum;
			buf[x1][i] = '#';
		}
	}
	for (int i = x0; i <= x1; ++ i) {
		if (buf[i][y0] != '#') {
			++ sum;
			buf[i][y0] = '#';
		}
		if (buf[i][y1] != '#') {
			++ sum;
			buf[i][y1] = '#';
		}
	}
}

void Check0() {
	if (rr[0] < 2 || cc[0] < 2) {
		PN;
		return;
	}
	int x0 = rr[1], y0 = 1;
	while (buf[x0][cc[y0]] != '#') ++ y0;
	y0 = cc[y0];
	for (int i = 2; i <= rr[0]; ++ i)
		for (int j = 2; j <= cc[0]; ++ j)
			if (C(x0, y0, rr[i], cc[j])) {
				for (int a = 1; a <= rr[0]; ++ a)
					for (int b = 1; b <= cc[0]; ++ b)
						for (int c = a + 1; c <= rr[0]; ++ c)
							for (int d = b + 1; d <= cc[0]; ++ d)
								if (C(rr[a], cc[b], rr[c], cc[d])) {
									D(x0, y0, rr[i], cc[j]);
									D(rr[a], cc[b], rr[c], cc[d]);
									if (!sum) {
										PY;
										printf("%d %d %d %d\n%d %d %d %d\n", x0, y0, rr[i], cc[j], rr[a], cc[b], rr[c], cc[d]);
										return;
									}
									E(rr[a], cc[b], rr[c], cc[d]);
									E(x0, y0, rr[i], cc[j]);
								}
			}
	PN;
}

void Check1() {
	if (rr[0] > 4 && cc[0] != 4) {
		PN;
		return;
	}
	if (cc[0] > 4 && rr[0] != 4) {
		PN;
		return;
	}
	if (rr[0] > 4) {
		for (int a = 1; a <= 2; ++ a) for (int c = 1; c <= 2; ++ c)
			for (int b = rr[0] - 1; b <= rr[0]; ++ b) for (int d = rr[0] - 1; d <= rr[0]; ++ d) {
				if (C(rr[c], cc[1], rr[d], cc[3]) && C(rr[a], cc[2], rr[b], cc[4])) {
					D(rr[c], cc[1], rr[d], cc[3]), D(rr[a], cc[2], rr[b], cc[4]);
					if (!sum) {
						PY;
						printf("%d %d %d %d\n%d %d %d %d\n", rr[c], cc[1], rr[d], cc[3], rr[a], cc[2], rr[b], cc[4]);
						return;
					}
					E(rr[c], cc[1], rr[d], cc[3]), E(rr[a], cc[2], rr[b], cc[4]);
				}
		}
	}
	else {
		for (int a = 1; a <= 2; ++ a) for (int c = 1; c <= 2; ++ c)
			for (int b = cc[0] - 1; b <= cc[0]; ++ b) for (int d = cc[0] - 1; d <= cc[0]; ++ d) {
				if (C(rr[1], cc[c], rr[3], cc[d]) && C(rr[2], cc[a], rr[4], cc[b])) {
					D(rr[1], cc[c], rr[3], cc[d]), D(rr[2], cc[a], rr[4], cc[b]);
					if (!sum) {
						PY;
						printf("%d %d %d %d\n%d %d %d %d\n", rr[1], cc[c], rr[3], cc[d], rr[2], cc[a], rr[4], cc[b]);
						return;
					}
					E(rr[1], cc[c], rr[3], cc[d]), E(rr[2], cc[a], rr[4], cc[b]);
				}
		}
	}
	PN;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", buf[i] + 1);
		for (int j = 1; j <= m; ++ j) {
			row[i][j] = row[i][j - 1] + (buf[i][j] == '#');
			col[i][j] = col[i - 1][j] + (buf[i][j] == '#');
			if (buf[i][j] == '#') {
				++ sum;
				dr[i][j] = dr[i][j - 1] + 1;
				dc[i][j] = dc[i - 1][j] + 1;
				r[i] = max(r[i], dr[i][j]);
				c[j] = max(c[j], dc[i][j]);
			}
		}
	}
	for (int i = 1; i <= n; ++ i)
		if (r[i] >= 3) rr[++ rr[0]] = i;
	for (int j = 1; j <= m; ++ j)
		if (c[j] >= 3) cc[++ cc[0]] = j;
	if (rr[0] <= 4 && cc[0] <= 4)
		Check0();
	else 
		Check1();
	return 0;
}
