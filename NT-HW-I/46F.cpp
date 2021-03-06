#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1000, kMaxM = 1000, kMaxK = 1000;
int n, m, k, cnt, begin[kMaxN], end[kMaxM << 1], next[kMaxM << 1];
map<string, int> idx;
bool ea[kMaxM], eb[kMaxM];

struct State {
	int room[kMaxK];
	int keys[kMaxM];
} start, final;

int root[kMaxN];

int Root(int x) {
	return (x == root[x] ? x : root[x] = Root(root[x]));
}

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Check(bool *e) {
	for (int i = 0; i < n; ++ i) root[i] = i;
	bool refresh = true;
	while (refresh) {
		refresh = false;
		for (int i = 0; i < cnt; i += 2) {
			if (e[i >> 1]) continue;
			int u = end[i], v = end[i ^ 1], c = start.keys[i >> 1];
			u = Root(u), v = Root(v), c = Root(c);
			if (u == c || v == c) {
				root[u] = v;
				e[i >> 1] = true;
				refresh = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for (int u, v; m --; ) {
		cin >> u >> v;
		-- u, -- v;
		AddEdge(u, v), AddEdge(v, u);
	}
	for (int i = 0, x; i < k; ++ i) {
		static string nam;
		cin >> nam;
		idx[nam] = i;
		cin >> start.room[i];
		-- start.room[i];
		cin >> x;
		for (int y; x --; ) {
			cin >> y;
			start.keys[y - 1] = start.room[i];
		}
	}
	Check(ea);
	for (int i = 0, x; i < k; ++ i) {
		static string nam;
		cin >> nam;
		int id = idx[nam];
		cin >> final.room[id];
		-- final.room[id];
		cin >> x;
		if (Root(final.room[id]) != Root(start.room[id])) {
			cout << "NO\n";
			return 0;
		}
		for (int y; x --; ) {
			cin >> y;
			final.keys[y - 1] = final.room[id];
			if (Root(final.room[id]) != Root(start.keys[y - 1])) {
				cout << "NO\n";
				return 0;
			}
		}
	}
	swap(start, final);
	Check(eb);
	for (int i = 0; i < cnt; i += 2)
		if (ea[i >> 1] != eb[i >> 1]) {
			cout << "NO\n";
			return 0;
		}
	cout << "YES\n";
	return 0;
}
