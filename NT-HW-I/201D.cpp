#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int kMaxN = 15, kMaxM = 500000, kInf = 0x3f3f3f3f;
int n, m, t;
char buf[16];
char des[kMaxN][16];
char src[kMaxM][16];
int dp[kMaxN * (kMaxN - 1) / 2 + 1][1 << kMaxN];
int log2[1 << kMaxN];
vector<int> pos[kMaxN];
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
        log2[1 << i] = i;
    for (int i = 0; i < n; ++ i)
        scanf("%s", des[i]);
    scanf("%d", &t);
    int res = kInf, rec = -1;
    for (int o = 0; o < t; ++ o) {
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) 
            scanf("%s", src[i]);
        for (int i = 0; i < n; ++ i)
            pos[i].clear();
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
                if (strcmp(src[j], des[i]) == 0) pos[i].push_back(j);
        for (int i = 0; i < n; ++ i) pos[i].push_back(m);
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int mask = 0; mask < (1 << n); ++ mask) {
            int now = ~mask & ((1 << n) - 1);
            int cur = __builtin_popcount(mask);
            while (now) {
                int p = now & -now;
                now ^= p;
                p = log2[p];
                for (int inv = 0; inv <= cur * (cur - 1) / 2; ++ inv)
                    if (dp[inv][mask] != kInf) {
                        int tmp = *lower_bound(pos[p].begin(), pos[p].end(), dp[inv][mask]);
                        if (tmp != m) {
                            int n_inv = inv + cur - __builtin_popcount(mask & ((1 << p) - 1));
                            int n_mask = mask ^ (1 << p);
                            dp[n_inv][n_mask] = min(dp[n_inv][n_mask], tmp + 1);
                        }
                    }
            }
        }
        int inv;
        for (inv = 0; inv <= n * (n - 1) / 2; ++ inv)
            if (dp[inv][(1 << n) - 1] != kInf) break;
        if (inv > n * (n - 1) / 2) continue;
        if (inv < res) {
            res = inv;
            rec = o;
        }
    }
    if (rec == -1)
        printf("Brand new problem!\n");
    else {
        printf("%d\n", rec + 1);
        printf("[:");
        for (int i = n * (n - 1) / 2 - res + 1; i --; )
            printf("|");
        printf(":]\n");
    }
    return 0;
}
