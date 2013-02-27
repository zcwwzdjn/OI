#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 100;
int n, aa[26], bb[26], req[26];
string a[kMaxN], b[kMaxN];
bool vis[kMaxN];
int mat[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		cin >> a[i];
		++ aa[a[i][0] - 'A'];
	}
	for (int i = 0; i < n; ++ i) {
		cin >> b[i];
		++ bb[b[i][0] - 'A'];
	}
	sort(a, a + n), sort(b, b + n);
	int cnt = 0;
	for (int i = 0; i < 26; ++ i) cnt += (req[i] = min(aa[i], bb[i]));
	for (int i = 0; i < n; ++ i) {
		if (req[a[i][0] - 'A'] < aa[a[i][0] - 'A']) {
			int j = 0;
			for ( ; j < n && (vis[j] || (b[j][0] != a[i][0] && req[b[j][0] - 'A'] == bb[b[j][0] - 'A'])); ++ j);
			vis[mat[i] = j] = true;
			if (a[i][0] == b[j][0]) -- req[a[i][0] - 'A'];
			-- aa[a[i][0] - 'A'];
			-- bb[b[j][0] - 'A'];
		}
		else {
			int j = 0;
			for ( ; j < n && (vis[j] || b[j][0] != a[i][0]); ++ j);
			vis[mat[i] = j] = true;
			-- req[a[i][0] - 'A'];
			-- aa[a[i][0] - 'A'];
			-- bb[b[j][0] - 'A'];
		}
	}
	for (int i = 0; i < n; ++ i) {
		if (i) cout << ", ";
		cout << a[i] << " " << b[mat[i]];
	}
	cout << endl;
	return 0;
}
