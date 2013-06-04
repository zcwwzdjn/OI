#include <cstdio>
#include <utility>
#include <set>

using namespace std;

int n;
set<pair<int, int> > s;

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n - 1; ++ i) {
		static char cmd[2];
		static int x;
		scanf("%s%d", cmd, &x);
		if (cmd[0] == 'd') s.insert(make_pair(x, i));
		else {
			while ((int)s.size() >= x)
				s.erase(s.begin());
		}
	}
	scanf("%*s%d", &n);
	if ((int)s.size() < n) puts("-1");
	else {
		set<int> l;
		int sum = 0;
		for (set<pair<int, int> >::iterator it = s.begin(); it != s.end(); ++ it) {
			l.insert(it->second);
			sum += it->first;
		}
		printf("%d\n%d\n", sum, (int)l.size());
		for (set<int>::iterator it = l.begin(); it != l.end(); ++ it) {
			static bool fir = true;
			if (fir) fir = false;
			else putchar(' ');
			printf("%d", (*it) + 1);
		}
		puts("");
	}
	return 0;
}
