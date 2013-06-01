#include <cstdio>
#include <cstring>

char buf[1 << 17];
int stop;
bool rec[1 << 17];

int main() {
	fgets(buf, 1 << 17, stdin);
	int n = strlen(buf);
	int res = 0;
	for (int i = 0; i < n; ++ i)
		if (buf[i] == '(') {
			if (stop) rec[stop - 1] = true;
			rec[stop ++] = false;
		}
		else if (buf[i] == ')') {
			if (!stop) ++ res;
			else {
				if (rec[stop - 1]) res += 2;
				-- stop;
			}
		}
		else if (!((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] == ' '))) {
			if (stop) rec[stop - 1] = true;
		}
	res += stop;
	printf("%d\n", res);
	return 0;
}
