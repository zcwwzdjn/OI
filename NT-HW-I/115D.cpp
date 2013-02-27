#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

const int kMod = 1000003;
char buf[2048];
int dp[2048];

#define UPT(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

int main() {
	scanf("%s", buf);
	int n = strlen(buf);
	for (int i = 0; i < n; )
		if (buf[i] >= '0' && buf[i] <= '9') {
			int j = i;
			while (j < n && buf[j] >= '0' && buf[j] <= '9') ++ j;
			for (int k = i; k < j - 1; ++ k) buf[k] = '\0';
			buf[j - 1] = '0';
			i = j;
		}
		else {
			if (buf[i] == '-') buf[i] = '+';
			if (buf[i] == '/') buf[i] = '*';
			if (buf[i] == '*' && (i == 0 || !isdigit(buf[i - 1]))) {
				puts("0");
				return 0;
			}
			++ i;
		}
	if (!isdigit(buf[n - 1])) {
		puts("0");
		return 0;
	}
	int m = 0;
	for (int i = 0; i < n; ++ i)
		if (buf[i]) buf[m ++] = buf[i];
	buf[m] = '\0';
	n = m;
	dp[0] = 1;
	m = 0;
	for (int i = 0; i < n; ++ i)
		if (!isdigit(buf[i])) {
			memmove(dp + 1, dp, sizeof(int) * ++ m);
			dp[0] = 0;
		}
		else for (int j = m - 1; j >= 0; -- j) UPT(dp[j], dp[j + 1]);
	printf("%d\n", dp[0]);
	return 0;
}
