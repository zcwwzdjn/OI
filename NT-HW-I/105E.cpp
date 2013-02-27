#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NONE 0
#define ONE 1
#define TWO 2
#define DONE 3

#define NMOVE 0
#define MOVED 1

#define pb push_back

typedef unsigned long long Hash;

Hash Calc(const vector<int> &cur) {
	Hash res = 0;
	for (int i = 0; i < 9; ++ i) res = res * 99991 + cur[i];
	return res;
}

set<Hash> hash;
int po[3], mr[3], tr[3];
int ans;
vector<int> start;

bool CheckCanMove(int x, int *po, int *mv) {
	if (mv[x] == MOVED) return false;
	int y = (x + 1) % 3, z = (y + 1) % 3;
	if (po[y] == po[x] || po[z] == po[x]) return false;
	return true;
}

bool CheckCanLift(int x, int *po, int *th) {
	if (th[x] != NONE) return false;
	int y = (x + 1) % 3, z = (y + 1) % 3;
	if (po[y] == po[x] || po[z] == po[x]) return false;
	return true;
}

bool CheckCanThrow(int x, int *po, int *th) {
	if (th[x] != ONE && th[x] != TWO) return false;
	if (th[x] == TWO) return true;
	int y = (x + 1) % 3, z = (y + 1) % 3;
	int t = (po[x] == po[y]) + (po[x] == po[z]);
	if (t == 1) return true;
	return false;
}

void Dfs(vector<int> cur) {
	if (ans == 42) return;
	Hash h = Calc(cur);
	if (hash.count(h)) return;
	hash.insert(h);
	int po[3], mv[3], th[3];
	for (int i = 0; i < 3; ++ i) {
		ans = max(ans, po[i] = cur[i * 3 + 0]);
		mv[i] = cur[i * 3 + 1];
		th[i] = cur[i * 3 + 2];
	}
	for (int x = 0; x < 3; ++ x) {
		int y = (x + 1) % 3, z = (y + 1) % 3;
		if (CheckCanMove(x, po, mv))
			for (int j = -mr[x]; j <= mr[x]; ++ j) if (j != 0)
				if (po[x] + j > 0 && po[y] != po[x] + j && po[z] != po[x] + j) {
					cur[x * 3 + 0] += j;
					cur[x * 3 + 1] = MOVED;
					Dfs(cur);
					cur[x * 3 + 1] = NMOVE;
					cur[x * 3 + 0] -= j;
				}
	}
	for (int x = 0; x < 3; ++ x) if (CheckCanLift(x, po, th)) {
		int y = (x + 1) % 3, z = (y + 1) % 3;
		if (po[y] == po[z] && abs(po[y] - po[x]) == 1) {	
			cur[y * 3 + 0] = po[x];
			cur[z * 3 + 0] = po[x];
			cur[x * 3 + 2] = TWO;
			Dfs(cur);
			cur[x * 3 + 2] = th[x];
			cur[z * 3 + 0] = po[z];
			cur[y * 3 + 0] = po[y];
		}
		else {
			for (int i = 1; i < 3; ++ i) {
				int y = (x + i) % 3;
				if (abs(po[y] - po[x]) == 1) {
					cur[y * 3 + 0] = po[x];
					cur[x * 3 + 2] = ONE;
					Dfs(cur);
					cur[x * 3 + 2] = th[x];
					cur[y * 3 + 0] = po[y];
				}
			}
		}
	}
	for (int x = 0; x < 3; ++ x) if (CheckCanThrow(x, po, th)) {
		int y = (x + 1) % 3, z = (y + 1) % 3;
		cur[x * 3 + 2] = DONE;
		for (int j = -tr[x]; j <= tr[x]; ++ j) if (j != 0)
			if (po[x] + j > 0 && (po[y] != po[x] || po[x] + j != po[y]) && (po[z] != po[x] || po[x] + j != po[z])) {
				if (po[y] == po[x]) cur[y * 3 + 0] = po[x] + j;
				if (po[z] == po[x]) cur[z * 3 + 0] = po[x] + j;
				Dfs(cur);
				if (po[z] == po[x]) cur[z * 3 + 0] = po[z];
				if (po[y] == po[x]) cur[y * 3 + 0] = po[y];
			}
		cur[x * 3 + 2] = th[x];
	}
}

int main() {
	for (int i = 0; i < 3; ++ i) {
		scanf("%d%d%d", &po[i], &mr[i], &tr[i]);
		start.pb(po[i]);
		start.pb(0), start.pb(0);
	}
	Dfs(start);
	printf("%d\n", ans);
	return 0;
}
