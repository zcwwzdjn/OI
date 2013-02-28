/*
 * $File: opt.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a sequence with some elements in it
 *   and each element is supposed to go to some
 *   other index. You can copy a element to another, 
 *   which costs 1, and you can swap 2 elements,
 *   which costs 2. Return a solution with smallest
 *   cost.
 *
 * Solution:
 *   First of all just copy elements which can be
 *   move to target in 1 move. Then we get many circles.
 *   As for circles whose length is 2, just swap them, and
 *   for other circles, if there is a empty cell, move 1 to the
 *   cell and move the rest of elements to their targets.
 *   Nice greedy problem.
 */

#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair

const int kMaxN = 10000, kMaxP = 10000;
int N, P;
vector<pair<int, int> > seq[kMaxP];
int pos[kMaxN];
int cur[kMaxN];

int main() {
	scanf("%d%d", &N, &P);
	for (int i = 0; i < P; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
		-- x;
		for (int a, b; y --; ) {
			scanf("%d%d", &a, &b);
			-- a;
			seq[x].pb(mp(a, b));
		}
	}
	int idx = 0;
	memset(pos, -1, sizeof(pos));
	memset(cur, -1, sizeof(cur));
	for (int i = 0; i < P; ++ i) {
		int y = seq[i].size();
		for (int j = 0; j < y; ++ j)
			for (int k = 0; k < seq[i][j].second; ++ k) {
				pos[idx] = seq[i][j].first + k;
				cur[seq[i][j].first + k] = idx;
				++ idx;
			}
	}
	int cost = 0;
	while (true) {
		int last = cost;
		for (int i = 0; pos[i] != -1; ++ i) {
			if (cur[i] == -1) {
				cost += 1;
				printf("K %d %d 1\n", pos[i] + 1, i + 1);
				swap(cur[i], cur[pos[i]]);
				pos[i] = i;
			}
			else if (cur[i] != i && cur[i] == pos[i]) {
				cost += 2;
				printf("Z %d %d 1\n", pos[i] + 1, i + 1);
				pos[cur[i]] = pos[i];
				swap(cur[i], cur[pos[i]]);
				pos[i] = i;
			}
		}
		if (last == cost) break;
	}
	int rec = -1;
	for (int i = 0; i < N; ++ i)
		if (cur[i] == -1) rec = i;
	if (rec == -1) {
		for (int i = 0; pos[i] != -1; ++ i)
			if (cur[i] != i) {
				cost += 2;
				printf("Z %d %d 1\n", pos[i] + 1, i + 1);
				pos[cur[i]] = pos[i];
				swap(cur[i], cur[pos[i]]);
				pos[i] = i;
			}
	}
	else {
		while (true) {
			int last = cost;
			int tmp = -1;
			for (int i = 0; pos[i] != -1; ++ i)
				if (cur[i] != i && tmp == -1) tmp = i;
			if (tmp != -1) {
				cost += 1;
				printf("K %d %d 1\n", pos[tmp] + 1, rec + 1);
				swap(cur[pos[tmp]], cur[rec]);
				pos[tmp] = rec;
				while (true) {
					int last = cost;
					for (int i = 0; pos[i] != -1; ++ i) {
						if (i != tmp && cur[i] == -1) {
							cost += 1;
							printf("K %d %d 1\n", pos[i] + 1, i + 1);
							swap(cur[i], cur[pos[i]]);
							pos[i] = i;
						}
					}
					if (last == cost) break;
				}
				cost += 1;
				printf("K %d %d 1\n", rec + 1, tmp + 1);
				swap(cur[rec], cur[tmp]);
				pos[tmp] = tmp;
			}
			if (last == cost) break;
		}
	}
	if (!cost) puts("NIC");
	return 0;
}
