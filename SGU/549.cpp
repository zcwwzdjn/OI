#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> rec[4000];
int tmp[4000];

bool Cmp(const vector<int> &a, const vector<int> &b) {
	return (a.size() > b.size());
}

int main() {
	scanf("%d%d", &n, &k);
	for (int m, c; n --; ) {
		scanf("%d%d", &m, &c);
		-- m;
		rec[m].push_back(c);
	}
	sort(rec, rec + 4000, Cmp);
	int cnt = rec[k - 1].size();
	for (int i = 0; i < 4000; ++ i) {
		sort(rec[i].begin(), rec[i].end());
		if (rec[i].size() >= cnt) {
			for (int j = 0; j < cnt; ++ j)
				tmp[i] += rec[i][rec[i].size() - 1 - j];
		}
	}
	sort(tmp, tmp + 4000);
	int sum = 0;
	for (int i = 0; i < k; ++ i) sum += tmp[4000 - 1 - i];
	printf("%d %d\n", cnt, sum);
	return 0;
}
