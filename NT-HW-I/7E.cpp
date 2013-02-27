#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define SAF 0
#define SUS 1
#define ADD 2
#define MUL 3

typedef unsigned long long Hash;
const int kSeed = 99991;
char buf[128];

Hash CalcHash(char *str) {
	Hash res = 0;
	while (*str) res = res * kSeed + *(str ++);
	return res;
}

Hash CalcHash(char *str, int l, int r) {
	Hash res = 0;
	for (int i = l; i <= r; ++ i)
		res = res * kSeed + str[i];
	return res;
}

int n, pri[256];
map<Hash, int> val;

int Solve(int l, int r) {
	int pr = -1, po, cn = 0;
	char re;
	for (int i = l; i <= r; ++ i) {
		if (buf[i] == '(') ++ cn;
		if (buf[i] == ')') -- cn;
		if (cn == 0 && pri[buf[i]] && (pr == -1 || pri[buf[i]] <= pr)) {
			pr = pri[buf[i]];
			po = i;
			re = buf[i];
		}
	}
	if (pr == -1) {
		if (buf[l] == '(') return (Solve(l + 1, r - 1) == SUS ? SUS : SAF);
		else {
			Hash hash = CalcHash(buf, l, r);
			if (val.count(hash)) return val[hash];
			else return SAF;
		}
	}
	int ll = Solve(l, po - 1), rr = Solve(po + 1, r);
	if (ll == SUS || rr == SUS) return SUS;
	if (pr == 1) {
		if (re == '+') return ADD;
		else if (re == '-') {
			if (rr == ADD) return SUS;
			return ADD;
		}
	}
	else {
		if (ll == ADD || rr == ADD) return SUS;
		if (re == '*') return MUL;
		else if (re == '/') {
			if (rr == MUL) return SUS;
			return MUL;
		}
	}
}

void Trim(char *str) {
	char *des = str;
	while (*str) {
		char t = *(str ++);
		if (t != ' ') *(des ++) = t;
	}
	*des = '\0';
}

int main() {
	pri['+'] = pri['-'] = 1, pri['*'] = pri['/'] = 2;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static char tmp[16], nam[128];
		scanf("%s", tmp);
		if (strlen(tmp) == 1) scanf("%s", tmp);
		scanf("%s", nam);
		fgets(buf, 128, stdin);
		buf[strlen(buf) - 1] = '\0';
		Trim(buf);
		val[CalcHash(nam)] = Solve(0, strlen(buf) - 1);
	}
	fgets(buf, 128, stdin);
	buf[strlen(buf) - 1] = '\0';
	Trim(buf);
	puts(Solve(0, strlen(buf) - 1) == SUS ? "Suspicious" : "OK");
	return 0;
}
