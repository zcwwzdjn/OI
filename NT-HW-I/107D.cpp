#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int kMod = 12345;
long long n;
int c, a, b, s, rec[26], mul[26], pos[26];
vector<int> seq[26], sol, state[123];
map<vector<int>, int> idx;
int cnt;

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

struct Matrix {
	int v[123][123];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	Matrix() {
		clear();
	}
} e, f, d;

Matrix operator * (const Matrix &a, const Matrix &b) {
	Matrix c;
	for (int i = 0; i < s; ++ i)
		for (int j = 0; j < s; ++ j)
			for (int k = 0; k < s; ++ k)
				UPT(c.v[i][j], a.v[i][k] * b.v[k][j] % kMod);
	return c;
}

Matrix PowMod(const Matrix &a, long long b) {
	Matrix res = e, tmp = a;
	while (b) {
		if (b & 1) res = res * tmp;
		b >>= 1;
		tmp = tmp * tmp;
	}
	return res;
}

int Gcd(int a, int b) {
	return (b ? Gcd(b, a % b) : a);
}

void Mark(int step) {
	if (step == b) {
		state[cnt] = sol;
		idx[sol] = cnt ++;
	}
   	else {
		for (int i = 0; i < mul[step]; ++ i) {
			sol.push_back(i);
			Mark(step + 1);
			sol.pop_back();
		}
	}	
}

int main() {
	scanf("%I64d%d", &n, &c);
	for (int i = 0; i < c; ++ i) {
		char buf[2];
		int x;
		scanf("%s%d", buf, &x);
		seq[buf[0] - 'A'].push_back(x);
	}
	s = 1;
	for (int i = 0; i < 26; ++ i)
		if (seq[i].size()) {
			sort(seq[i].begin(), seq[i].end());
			seq[i].resize(unique(seq[i].begin(), seq[i].end()) - seq[i].begin());
			int m = 0;
			for (int j = 0; j < int(seq[i].size()); ++ j) {
				bool fail = false;
				for (int k = 0; k < j; ++ k)
					if (seq[i][j] % seq[i][k] == 0) {
						fail = true;
						break;
					}
				if (!fail) seq[i][m ++] = seq[i][j];
			}
			seq[i].resize(m);
			if (seq[i].back() == 1) {
				++ a;
				continue;
			}
			rec[b] = i;
			pos[i] = b;
			int x = 1;
			for (int j = 0; j < int(seq[i].size()); ++ j) x = x / Gcd(x, seq[i][j]) * seq[i][j];
			mul[b ++] = x;
			s *= x;
		}
	Mark(0);
	for (int i = 0; i < cnt; ++ i) {
		vector<int> u = state[i];
		for (int j = 0; j < 26; ++ j) if (seq[j].size()) {
			if (seq[j].back() == 1) ++ f.v[i][i];
			else {
				int tmp = u[pos[j]];
				u[pos[j]] = (u[pos[j]] + 1) % mul[pos[j]];
				++ f.v[idx[u]][i];
				u[pos[j]] = tmp;
			}
		}
	}
	for (int i = 0; i < s; ++ i) e.v[i][i] = 1;
	d.v[0][0] = 1;
	d = PowMod(f, n) * d;
	int ans = 0;
	for (int i = 0; i < cnt; ++ i) {
		vector<int> u = state[i];
		bool fail = false;
		for (int j = 0; j < b; ++ j) {
			if (u[j] == 0) continue;
			bool ffail = true;
			for (int k = 0; k < int(seq[rec[j]].size()); ++ k)
				if (u[j] % seq[rec[j]][k] == 0) {
					ffail = false;
					break;
				}
			if (ffail) {
				fail = true;
				break;
			}
		}
		if (!fail) UPT(ans, d.v[i][0]);
	}
	printf("%d\n", ans);
	return 0;
}
