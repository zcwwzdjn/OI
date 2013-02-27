#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

namespace {
	typedef pair<int, int> Pair;
	const int kMaxN = 100000;
	int n, m;
	bool del[kMaxN + 1];
	priority_queue<Pair> heap;
	vector<Pair> ans;

	struct Node {
		int x, h, c, b;
		Node() {}
		Node(int x_, int h_, int c_, int b_) : x(x_), h(h_), c(c_), b(b_) {}
		bool operator < (const Node &t) const {
			if (x != t.x) return (x < t.x);
			if (h != t.h) return (h > t.h);
			return (c > t.c);
		}
	} node[kMaxN * 2];

	void Solve() {
		//freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
		scanf("%d", &n);
		for (int i = 0, h, l, r; i < n; ++ i) {
			scanf("%d%d%d", &h, &l, &r);
			node[m ++] = Node(l, h, 1, i);
			node[m ++] = Node(r, h, -1, i);
		}
		sort(node, node + m);
		heap.push(make_pair(0, n));
		for (int i = 0; i < m; ++ i) {
			while (del[heap.top().second]) heap.pop();
			if (node[i].c == 1) {
				if (node[i].h > heap.top().first) {
					ans.push_back(make_pair(node[i].x, heap.top().first));
					ans.push_back(make_pair(node[i].x, node[i].h));
				}
				heap.push(make_pair(node[i].h, node[i].b));
			}
			else {
				if (node[i].b == heap.top().second) {
					heap.pop();
					while (del[heap.top().second]) heap.pop();
					if (node[i].h > heap.top().first) {
						ans.push_back(make_pair(node[i].x, node[i].h));
						ans.push_back(make_pair(node[i].x, heap.top().first));
					}
				}
				del[node[i].b] = true;
			}
		}
		m = 0;
		for (int i = 0, j = 0; i < int(ans.size()); i = j) {
			while (j < int(ans.size()) && ans[i].first == ans[j].first) ++ j;
			ans[m ++] = ans[i];
			ans[m ++] = ans[j - 1];
		}
		ans.resize(m);
		printf("%d\n", ans.size());
		for (int i = 0; i < int(ans.size()); ++ i) printf("%d %d\n", ans[i].first, ans[i].second);
	}
}

int main() {
	::Solve();
	return 0;
}
