#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
long long Calc(int n, int x) {
    long long res = 0LL;
    long long c = 1LL;
    for (int i = 0; i <= x; ++ i) {
        if (n <= c) {
            res += (long long)i * n;
            return res;
        }
        res += (long long)c * i;
        n -= c;
        c = c * (x - i) / (i + 1);
    }
    return 0x3f3f3f3f3f3f3f3fLL;
}
int Solve(int n, int m) {
    m = min(m, n >> 1);
    int lb = -1, rb = n - 1;
    while (lb + 1 < rb) {
        int mid = (lb + rb) >> 1;
        if (Calc(n, mid) <= (long long)mid * m) rb = mid;
        else lb = mid;
    }
    return rb;
}
int main() {
    int t, n, m;
    scanf("%d", &t);
    while (t --) {
        scanf("%d%d", &n, &m);
        printf("%d\n", Solve(n, m));
    }
    return 0;
}
