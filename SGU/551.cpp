#include <cstdio>
#include <utility>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> Pair;
priority_queue<Pair, vector<Pair>, greater<Pair> > heap;
int n, t[2];

int main() {
	scanf("%d%d%d", &n, &t[0], &t[1]);
	heap.push(make_pair(t[0], 0));
	heap.push(make_pair(t[1], 1));
	int m = 0, f;
	while (m < n) {
		f = heap.top().first;
		bool can[2];
		can[0] = can[1] = false;
		while (heap.size() && heap.top().first == f) {
			can[heap.top().second] = true;	
			heap.pop();
			++ m;
		}
		if (m < n) {
			for (int i = 0; i < 2; ++ i)
				if (can[i]) heap.push(make_pair(f + t[i], i));
		}
	}
	while (heap.size()) {
		f = heap.top().first;
		heap.pop();
		++ m;
	}
	printf("%d %d\n", m, f);
	return 0;
}
