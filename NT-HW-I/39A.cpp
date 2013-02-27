#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kBufSize = 1024 * 1024;
int a, n, m;
char buf[kBufSize];

// b - a++, c - ++a

struct Node {
	int coef, type;
	bool operator < (const Node &t) const {
		if (coef != t.coef) return (coef < t.coef);
		if (coef < 0) return (type < t.type);
		else return (type > t.type);
	}
} node[1024 * 1024];

int main() {
	scanf("%d%s", &a, buf);
	n = strlen(buf);
	for (int i = 0; i < n; ++ i)
		if (buf[i] == 'a') {
			if (i - 2 >= 0 && buf[i - 1] == '+' && buf[i - 2] == '+') {
				buf[i] = 'c';
				buf[i - 1] = buf[i - 2] = '\0';
			}
			else {
				buf[i] = 'b';
				buf[i + 1] = buf[i + 2] = '\0';
			}
		}
	m = 0;
	for (int i = 0; i < n; ++ i)
		if (buf[i]) buf[m ++] = buf[i];
	n = m;
	buf[n] = '\0';
	reverse(buf, buf + n);
	if (buf[n - 1] != '-') {
		buf[n] = '+';
		buf[++ n] = '\0';
	}
	reverse(buf, buf + n);
	m = 0;
	for (int i = 0; i < n; ++ i)
		if (buf[i] == '+' || buf[i] == '-') {
			int &t = node[m].coef;
			int j = i + 1;
			if (buf[j] < '0' || buf[j] > '9') t = 1;
			else 
				while (buf[j] >= '0' && buf[j] <= '9') t = t * 10 + buf[j ++] - '0';
			if (buf[i] == '-') t = -t;
			if (buf[j] == '*') ++ j;
			node[m ++].type = buf[j] - 'b';
		}
	sort(node, node + m);
	int res = 0;
	for (int i = 0; i < m; ++ i) {
		if (node[i].type == 1) ++ a;
		res += node[i].coef * a;
		if (node[i].type == 0) ++ a;
	}
	printf("%d\n", res);
	return 0;
}
