#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, a[kMaxN], b[kMaxN];
vector<pair<vector<int>, vector<int> > > sol, rec[5];
int cnt[5];
bool vis[kMaxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &a[i]);
		b[-- a[i]] = i;
	}
	for (int i = 0; i < n; ++ i)
		if (!vis[i]) {
			vector<int> tmp;
			tmp.push_back(i);
			vis[i] = true;
			for ( ; ; ) {
				int v = tmp.back();
				int u = a[v];
				if (vis[u]) break;
				vis[u] = true;
				tmp.push_back(u);
			}
			int j = 1, sz = tmp.size();
			if (sz == 1) continue;
			while (sz > 5) {
				vector<int> src, des;
				src.push_back(tmp[0]);
				for (int k = 0; k < 4; ++ k) src.push_back(tmp[j + k]);
				for (int k = 0; k < 5; ++ k)
					des.push_back(src[(k + 1) % 5]);
				sz -= 4;
				j += 4;
				sol.push_back(make_pair(src, des));
			}
			vector<int> src, des;
			src.push_back(tmp[0]);
			for (int k = j; k < (int)tmp.size(); ++ k) src.push_back(tmp[k]);
			sz = src.size();
			if (sz == 1) continue;
			for (int k = 0; k < sz; ++ k)
				des.push_back(src[(k + 1) % sz]);
			if (sz != 5)
				rec[sz].push_back(make_pair(src, des));
			else
				sol.push_back(make_pair(src, des));
		}
	for (int i = 0; i < (int)rec[4].size(); ++ i) sol.push_back(rec[4][i]);
	int v = min(rec[2].size(), rec[3].size());
	for (int i = 0; i < v; ++ i) {
		vector<int> src, des;
		for (int j = 0; j < 2; ++ j) src.push_back(rec[2][i].first[j]), des.push_back(rec[2][i].second[j]);
		for (int j = 0; j < 3; ++ j) src.push_back(rec[3][i].first[j]), des.push_back(rec[3][i].second[j]);
		sol.push_back(make_pair(src, des));
	}
	if ((int)rec[2].size() == v) {
		int rest = rec[3].size() - v;
		int split = rest / 3;
		for (int i = 0; i < split; ++ i) {
			for (int j = 1; j <= 2; ++ j) { 
				vector<int> src, des;
				src.push_back(rec[3][v + i].first[0]);
				src.push_back(rec[3][v + i].first[j]);
				des.push_back(rec[3][v + i].first[j]);
				des.push_back(rec[3][v + i].first[0]);
				rec[0].push_back(make_pair(src, des));
			}
		}
		v += split;
		for (int i = 0; i < (int)rec[0].size(); ++ i) {
			vector<int> src, des;
			for (int j = 0; j < 2; ++ j) src.push_back(rec[0][i].first[j]), des.push_back(rec[0][i].second[j]);
			for (int j = 0; j < 3; ++ j) src.push_back(rec[3][i + v].first[j]), des.push_back(rec[3][i + v].second[j]);
			sol.push_back(make_pair(src, des));
		}
		v += rec[0].size();
		for (int i = v; i < int(rec[3].size()); ++ i) sol.push_back(rec[3][i]);
	}
	else {
		for (int i = v; i < int(rec[2].size()); i += 2) {
			vector<int> src = rec[2][i].first, des = rec[2][i].second;
			if (i + 1 < (int)(rec[2].size())) {
				for (int j = 0; j < 2; ++ j) src.push_back(rec[2][i + 1].first[j]), des.push_back(rec[2][i + 1].second[j]);
			}
			sol.push_back(make_pair(src, des));
		}
	}
	printf("%d\n", sol.size());
	for (int i = 0; i < int(sol.size()); ++ i) {
		int s;
		printf("%d\n", s = sol[i].first.size());
		for (int j = 0; j < s; ++ j) {
			printf("%d", sol[i].first[j] + 1);
			if (j == s - 1) printf("\n");
			else printf(" ");
		}
		for (int j = 0; j < s; ++ j) {
			printf("%d", sol[i].second[j] + 1);
			if (j == s - 1) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}
