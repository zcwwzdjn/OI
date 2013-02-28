/*
 * $File: mok.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Some cups with some water, try to
 *   get to target with least moves.
 *
 * Solution:
 *   Bfs. Very original.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxQ = 50 * 50 * 50 * 50;
bool vis[kMaxQ];
int q[kMaxQ], qh, qt;
int n, buf[4], tmp[4], upper[4];
int start, final;

int Calc(int *seq) {
	int res = 0;
	for (int i = 0; i < n; ++ i) res = res * 50 + seq[i];
	return res;
}

bool Bfs() {
	int res = 0;
	while (qh < qt) {
		++ res;
		int ed = qt;
		while (qh < ed) {
			int u = q[qh ++];
			for (int i = n - 1; i >= 0; -- i) {
				buf[i] = u % 50;
				u /= 50;
			}
			for (int i = 0; i < n; ++ i)
				if (buf[i]) {
					memcpy(tmp, buf, sizeof(buf));
					tmp[i] = 0;
					int v = Calc(tmp);
					if (!vis[v]) {
						if (v == final) {
							printf("%d\n", res);
							return true;
						}
						vis[v] = true;
						q[qt ++] = v;
					}
				}
			for (int i = 0; i < n; ++ i)
				if (buf[i])
					for (int j = 0; j < n; ++ j)
						if (j != i) {
							memcpy(tmp, buf, sizeof(buf));
							tmp[i] = max(0, buf[i] - (upper[j] - buf[j]));
							tmp[j] = min(upper[j], buf[j] + buf[i]);
							int v = Calc(tmp);
							if (!vis[v]) {
								if (v == final) {
									printf("%d\n", res);
									return true;
								}
								vis[v] = true;
								q[qt ++] = v;
							}
						}
		}
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &buf[i]);
		upper[i] = buf[i];
	}
	start = Calc(buf);
	for (int i = 0; i < n; ++ i) scanf("%d", &buf[i]);
	final = Calc(buf);
	if (start == final) {
		puts("0");
		return 0;
	}
	vis[q[qt ++] = start] = true;
	if (!Bfs()) puts("NIE");
	return 0;
}
