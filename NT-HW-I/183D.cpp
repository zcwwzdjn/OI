#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

const double kEps = 1E-12;
const int kMaxN = 3000, kMaxM = 300;
int n, m;
double p[kMaxN][kMaxM];
double dp[2][kMaxN + 1];
vector<double> seq;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			scanf("%lf", &p[i][j]);
			p[i][j] /= 1000.0;
		}
	for (int j = 0; j < m; ++ j) {
		int des = 0, src = 1;
		for (int i = 0; i <= n; ++ i) dp[des][i] = dp[src][i] = 0.0;
		dp[des][0] = 1.0;
		double sum = 0.0;
		int len = 0;
		for (int i = 0; i < n; ++ i) {
			des ^= 1, src ^= 1;
			dp[des][0] = 1.0;
			for (int k = 0; k <= len; ++ k) {	
				dp[des][k + 1] = p[i][j] * dp[src][k] + (1.0 - p[i][j]) * dp[src][k + 1];
			}
			if (sum + dp[des][len + 1] < kEps)
				sum += dp[des][len + 1];
			else
				++ len;
		}
		for (int k = 1; k <= len; ++ k) {
			seq.push_back(dp[des][k]);
		}
	}
	double res = 0.0;
	sort(seq.begin(), seq.end(), greater<double>());
	for (int i = 0; i < n; ++ i) res += seq[i];
	printf("%.12lf\n", res);
	return 0;
}
