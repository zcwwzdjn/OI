/*
 * $File: sko.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   There are some stones on the axis.
 *   In each move you can choose a triple
 *   (p, p + 1, p + 2), erase 1 from p and
 *   p + 1 and add 1 to p + 2, or erase 1
 *   from p + 2 and add 1 to p and p + 1.
 *   Try to make there is at most 1 stone
 *   that 2 consecutive squares contain.
 *   You can assume there's exactly 1 final
 *   state.
 *
 * Solution:
 *   Firstly we can decrease the stones in
 *   each square to at most 2, according to
 *   the fact that (0,0,x,0,0)->(x/3,0,x%3,x/3).
 *   Then we can consider from right to left.
 *   When we come to p, we need to make sure
 *   that from p + 1 to the end the state is
 *   legal. So we make a classified discussion.
 *   Strange constructive algorithm.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int kOffset = 40;
int seq[10081];
int n;
queue<int> q;
bool inq[10081];

int main() {
	scanf("%d", &n);
	for (int x, y; n --; ) {
		scanf("%d%d", &x, &y);
		x += kOffset;
		seq[x] += y;
		if (seq[x] >= 3 && !inq[x]) {
			q.push(x);
			inq[x] = true;
		}
	}
	while (q.size()) {
		int u = q.front();
		q.pop(), inq[u] = false;
		for (int i = -1; i <= 1; i += 2) {
			int v = u + 2 * i;
			seq[v] += seq[u] / 3;
			if (seq[v] >= 3 && !inq[v]) {
				q.push(v);
				inq[v] = true;
			}
		}
		seq[u] %= 3;
	}
	for (int p = 10080; p >= 0; )
		if (seq[p]) {
			if (p + 1 <= 10080 && seq[p + 1]) {
				int d = min(seq[p], seq[p + 1]);
				seq[p] -= d, seq[p + 1] -= d, seq[p + 2] += d;
				p += 2;
			}
			else if (seq[p] == 2) {
				seq[p - 2] ++, seq[p + 1] ++, seq[p] = 0;
				++ p;
			}
			else if (seq[p] > 2) {
				seq[p - 2] += seq[p] / 3, seq[p + 2] += seq[p] / 3, seq[p] %= 3;
				p += 2;
			}
			else {
				-- p;
			}
		}
		else {
			-- p;
		}
	for (int x = 0, f = 1; x <= 10080; ++ x)
		if (seq[x]) {
			if (f) f = 0;
			else putchar(' ');
			printf("%d", x - kOffset);
		}
	puts("");
	return 0;
}
