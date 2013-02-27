#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int IsType2(int b, int d) {
	long long rec = 1;
	for (int i = 1; i <= 6; ++ i) {
		rec *= b;
		if (rec % d == 0) return i;
	}
	return 0;
}

int Gcd(int a, int b) {
	return (b ? Gcd(b, a % b) : a);
}

int main() {
	int b, d;
	scanf("%d%d", &b, &d);
	if (IsType2(b, d)) printf("2-type\n%d\n", IsType2(b, d));
	else if (b % d == 1) printf("3-type\n");
	else if (b % d == d - 1) printf("11-type\n");
	else {
		bool fail = true;
		for (int i = 2; i <= d && fail; ++ i)
			if (d % i == 0)
				for (int j = 2; j <= d / i && fail; ++ j)
					if ((d / i) % j == 0) {
						int k = d / i / j;
						if (Gcd(i, j) > 1 || Gcd(i, k) > 1 || Gcd(j, k) > 1) continue;
						if (k >= 2 && IsType2(b, i) && b % j == 1 && b % k == k - 1)
							fail = false;
						else if (k == 1) {
							if ((IsType2(b, i) && b % j == 1) || (IsType2(b, i) && b % j == j - 1) || (b % i == 1 && b % j == j - 1))
								fail = false;
						}
					}
		if (fail) printf("7-type\n");
		else printf("6-type\n");
	}
	return 0;
}
