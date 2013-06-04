#include <cstdio>
#include <utility>
#include <functional>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 50000;

typedef multiset<int> Set;
typedef pair<int, Set*> Pair;
priority_queue<Pair, vector<Pair>, greater<Pair> > heap[kMaxN];

int n, m, par[kMaxN], ind[kMaxN];
int val[kMaxN];
Set *rec[kMaxN];

int main() {
	scanf("%d%d", &n, &m);
	par[0] = -1;
	for (int i = 1; i < n; ++ i) {
		scanf("%d", &par[i]);
		-- par[i];
		++ ind[par[i]];
	}
	static int q[kMaxN], qh, qt;
	for (int i = n - m, v; i < n; ++ i) {
		scanf("%d", &v);
		rec[i] = new Set;
		rec[i]->insert(v);
		q[qt ++] = i;
	}
	for (int i = 0; i < n; ++ i) val[i] = 2147483647;
	while (qh < qt) {
		int u = q[qh ++];
		if (par[u] == -1) continue;
		heap[par[u]].push(make_pair(rec[u]->size(), rec[u]));
		val[par[u]] = min(val[par[u]], val[u]);
		if (!(-- ind[par[u]])) {
			q[qt ++] = par[u];
			while (heap[par[u]].size() > 1) {
				Set *src = heap[par[u]].top().second;
				heap[par[u]].pop();
				Set *des = heap[par[u]].top().second;
				heap[par[u]].pop();	
				for (Set::iterator it = src->begin(); it != src->end(); ++ it) {
					Set::iterator ti = des->insert(*it);
					if (ti != des->begin()) {
						Set::iterator prev = ti;
						-- prev;
						val[par[u]] = min(val[par[u]], *ti - *prev);
					}
					Set::iterator succ = ti;
					++ succ;
					if (succ != des->end()) {
						val[par[u]] = min(val[par[u]], *succ - *ti);
					}
				}
				heap[par[u]].push(make_pair(des->size(), des));
			}
			rec[par[u]] = heap[par[u]].top().second;
		}
	}
	for (int i = 0; i < n - m; ++ i) {
		if (i) putchar(' ');
		printf("%d", val[i]);
	}
	puts("");
	return 0;
}
