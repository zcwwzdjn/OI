#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
int n, m, s[kMaxN];
vector<int> ans;

int main() {
	scanf("%d%d", &n, &m);
	int mini = -1;
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &s[i]);
		if (mini == -1 || s[i] < s[mini]) mini = i;
	}
	bool res = true;
	if (m <= 0) res = false;
	else {
		int sum = 0;
		for (int i = 0; i < n; ++ i) sum += s[i];
		if (n == 1) {	
			if (m != sum) res = false;
			else
				for (int i = 0; i < s[0] << 1; ++ i) ans.push_back(0);
		}
		else {
			if (m > sum) res = false;
			else {
				if (m >= s[mini]) {
					ans.push_back(mini);
					for (int t = sum - m, i = 0; i < n && t; ++ i) if (i != mini) {
						while (t && s[i]) {
							ans.push_back(i), ans.push_back(i);
							-- s[i];
							-- t;
						}
					}
					ans.push_back(mini), -- s[mini];
					for (int i = 0; i < n; ++ i)
						while (s[i]) {
							ans.push_back(i), ans.push_back(i);
							-- s[i];
						}
				}
				else {
					if (m == 1) res = false;
					else {
						int tmp = (mini + 1) % n;
						for (int i = 0; i < m - 2; ++ i) {
							ans.push_back(mini);
							ans.push_back(tmp);
							ans.push_back(tmp);
							ans.push_back(mini);
							-- s[mini], -- s[tmp];
						}
						ans.push_back(mini);
						for (int i = 0; i < s[tmp] - 1; ++ i) {
							ans.push_back(tmp);
							ans.push_back(tmp);
						}
						ans.push_back(mini);
						-- s[mini];
						ans.push_back(tmp);
						s[tmp] = 0;
						for (int i = 0; i < n; ++ i)
							while (s[i]) {
								ans.push_back(i);
								ans.push_back(i);
								-- s[i];
							}
						ans.push_back(tmp);
					}
				}
			}
		}
	}
	if (!res) puts("No");
	else {
		puts("Yes");
		for (int i = 0; i < int(ans.size()); ++ i) {
			if (i) printf(" ");
			printf("%d", ans[i] + 1);
		}
		puts("");
	}
	return 0;
}
