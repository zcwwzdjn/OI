#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int, int> Pair;
typedef long long Int;
const int kMaxN = 250000;
int X, Y, P, R, N;
int x[kMaxN], y[kMaxN], m[kMaxN], p[kMaxN], r[kMaxN], s[kMaxN];
Pair q[kMaxN + 1];
Int d[kMaxN];
int qh, qt, ans, pt;
Int pos[kMaxN];
set<Pair> idt[kMaxN + 1];
#define LB(x) ((x) & (-(x)))
#define M(x, y) (make_pair(x, y))
#define lb lower_bound
int main() {
    scanf("%d%d%d%d%d", &X, &Y, &P, &R, &N);
    for (int i = 0; i < N; ++ i) {
        scanf("%d%d%d%d%d", &x[i], &y[i], &m[i], &p[i], &r[i]);
        x[i] -= X;
        y[i] -= Y;
        pos[pt ++] = d[i] = (Int)x[i] * x[i] + (Int)y[i] * y[i];
    }
    sort(pos, pos + pt);
    pt = unique(pos, pos + pt) - pos;
    for (int i = 0; i < N; ++ i) {
        int t = s[i] = lb(pos, pos + pt, d[i]) - pos;
        for (++ t; t <= pt; t += LB(t))
            idt[t].insert(M(m[i], i));
    }
    q[qt ++] = M(R, P);
    while (qh < qt) {
        R = q[qh].first;
        P = q[qh].second;
        ++ qh;
        int t = lb(pos, pos + pt, (Int)R * R) - pos;
        if (t == pt || pos[t] > (Int)R * R) -- t;
        for (++ t; t; t -= LB(t))
            while (true) {
                set<Pair>::iterator it = idt[t].lb(M(P + 1, 0));
                if (it == idt[t].begin()) break;
                -- it;
                q[qt ++] = M(r[it->second], p[it->second]);
                ++ ans;
                Pair er = *it;
                for (int i = s[it->second] + 1; i <= pt; i += LB(i))
                    idt[i].erase(er);
            }
    }
    printf("%d\n", ans);
    return 0;
}
