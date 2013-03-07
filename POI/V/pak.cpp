/*
 * $File: pak.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given some boxes whose sizes are all powers
 *   of 2, and some containers whose sizes are also
 *   powers of 2, find the minimal value that you
 *   can choose some boxes to fit tightly into the 
 *   containers.
 *
 * Solution:
 *   Greedy. Sort the containers by size. Use a
 *   heap to maintain the boxes, and you sometimes
 *   need to merge some boxes.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;
const int kMaxN = 10000, kMaxM = 5000;
priority_queue<Pair, vector<Pair>, greater<Pair> > heap;
int n, q, m, seq[kMaxM];

int main() {
	scanf("%d", &n);
	for (int x, y; n --; ) {
		scanf("%d%d", &x, &y);
		heap.push(make_pair(x, y));
	}
	scanf("%d", &q);
	for (int x, y; q --; ) {
		scanf("%d%d", &x, &y);
		while (y --) seq[m ++] = x;
	}
	sort(seq, seq + m);
	int res = 0;
	for (int i = 0; i < m; ++ i) {
		while (heap.size() > 1) {
			Pair a = heap.top();
			heap.pop();
			Pair b = heap.top();
			heap.pop();
			if (a.first >= seq[i] || b.first >= seq[i]) {
				heap.push(a);
				heap.push(b);
				break;
			}
			if (a.first == b.first)
				heap.push(make_pair(a.first + 1, a.second + b.second));
			else
				heap.push(b);
		}
		while (heap.size() && heap.top().first < seq[i]) heap.pop();
		if (heap.empty() || heap.top().first != seq[i]) {
			puts("NIE");
			return 0;
		}
		res += heap.top().second;
		heap.pop();
	}
	printf("%d\n", res);
	return 0;
}
