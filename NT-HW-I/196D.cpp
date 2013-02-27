#include <cstdio>
#include <cstring>
typedef unsigned long long Hash;
const int kMaxN = 400000, kSeed = 99991;
int n, m;
char buf[kMaxN + 2], des[kMaxN + 1];
Hash mypow[kMaxN + 1], str[kMaxN + 1], rev[kMaxN + 1];
bool Check() {
    int tmp = n;
    while (tmp && buf[tmp] == 'z') buf[tmp --] = 'a';
    if (tmp == 0) return false;
    ++ buf[tmp];
    return true;
}
bool Check(int rb, int len) {
    if (rb < len) return true;
    Hash a = str[rb] - str[rb - len] * mypow[len];
    Hash b = rev[rb] - rev[rb - len];
    return (a * mypow[rb - len] != b);
}
bool Dfs(int step, bool sgn) {
    if (step > n) {
        puts(des + 1);
        return true;
    }
    for (des[step] = (sgn ? buf[step] : 'a'); des[step] <= 'z'; ++ des[step]) {
        str[step] = str[step - 1] * kSeed + des[step];
        rev[step] = rev[step - 1] + mypow[step - 1] * des[step];
        if (Check(step, m) && Check(step, m + 1))
            if (Dfs(step + 1, sgn && (des[step] == buf[step]))) return true;
    }
    return false;
}
int main() {
    scanf("%d%s", &m, buf + 1);
    n = strlen(buf + 1);
    if (!Check()) {
        puts("Impossible");
        return 0;
    }
    mypow[0] = 1ULL;
    for (int i = 1; i <= n; ++ i) mypow[i] = mypow[i - 1] * kSeed;
    if (!Dfs(1, 1)) puts("Impossible");
    return 0;
}
