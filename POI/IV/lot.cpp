/*
 * $File: lot.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given the degree of each vertex in a
 *   graph, rebuild the graph. We can
 *   assume that at least 1 solution exists.
 *
 * Solution:
 *   Let us consider vertices from bigger degree
 *   to smaller. Greedily, if we now pick a vertex
 *   with degree D, we just connect it to the next
 *   D vertices. We can prove that in each turn we
 *   have enough vertices to be connected to the
 *   picked vertex. I use a heap to implement. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 500;
int n;
priority_queue<pair<int, int> > heap;

int main() {
	scanf("%d", &n);
	for (int i = 0, d; i < n; ++ i) {
		scanf("%d", &d);
		heap.push(make_pair(d, i));
	}
	while (heap.size()) {
		int d = heap.top().first;
		int v = heap.top().second;
		heap.pop();
		vector<pair<int, int> > rec;
		for (int i = 0; i < d; ++ i) {
			rec.push_back(heap.top());
			heap.pop();
		}
		for (int i = 0; i < d; ++ i) {
			printf("%d %d\n", v + 1, rec[i].second + 1);
			heap.push(make_pair(rec[i].first - 1, rec[i].second));
		}
	}
	return 0;
}
