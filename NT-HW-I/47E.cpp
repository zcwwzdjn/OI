#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<double, double> Pair;
const double kEps = 1E-8, kPi = acos(-1.0);
const int kMaxN = 10000, kMaxM = 100000;
int n, m, seq[kMaxM], s;
double v, agl[kMaxN];
Pair wall[kMaxM];
double need[kMaxM];

inline int sgn(double x) {
	if (fabs(x) < kEps) return 0;
	if (x > 0.0) return 1;
	return -1;
}

int main() {
	scanf("%d%lf", &n, &v);
	for (int i = 0; i < n; ++ i) scanf("%lf", &agl[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; ++ i) scanf("%lf%lf", &wall[i].first, &wall[i].second);
	sort(wall, wall + m);
	int rm = 0;
	for (int i = 0, j = 0; i < m; i = j) {
		while (j < m && sgn(wall[j].first - wall[i].first) == 0) ++ j;
		wall[rm ++] = wall[j - 1];
	}
	m = rm;
	for (int i = 0; i < m; ++ i) {
		double t = wall[i].first / (v * cos(kPi / 4.0));
		double y = v * sin(kPi / 4.0) * t - 4.9 * t * t;
		if (sgn(y - wall[i].second) <= 0) need[i] = 1E100;
		else {
			double lb = 0.0, rb = kPi / 4.0;
			for (int j = 0; j < 50; ++ j) {
				double mid = (lb + rb) * 0.5;
				t = wall[i].first / (v * cos(mid));
				y = v * sin(mid) * t - 4.9 * t * t;
				if (sgn(y - wall[i].second) <= 0) lb = mid;
				else rb = mid;
			}
			need[i] = lb;
		}
	}
	for (int i = 0; i < m; ++ i) {
		if (!s) seq[s ++] = i;
		else if (sgn(need[i] - need[seq[s - 1]]) > 0) seq[s ++] = i;
	}
	for (int i = 0; i < n; ++ i) {
		if (sgn(agl[i] - need[seq[s - 1]]) > 0) {
			double t = v * sin(agl[i]) / 4.9;
			printf("%.6lf %.6lf\n", v * cos(agl[i]) * t, 0.0);
		}
		else if (sgn(agl[i] - need[seq[0]]) <= 0) {
			double t = v * sin(agl[i]) / 4.9;
			double x = v * cos(agl[i]) * t;
			if (sgn(x - wall[seq[0]].first) < 0) printf("%.6lf %.6lf\n", x, 0.0);
			else {
				t = wall[seq[0]].first / (v * cos(agl[i]));
				double y = v * sin(agl[i]) * t - 4.9 * t * t;
				printf("%.6lf %.6lf\n", wall[seq[0]].first, y);
			}	
		}
		else {
			int lb = 0, rb = s;
			while (lb + 1 < rb) {
				int mid = (lb + rb) >> 1;
				if (sgn(agl[i] - need[seq[mid]]) <= 0) rb = mid;
				else lb = mid;
			}
			double t = v * sin(agl[i]) / 4.9;
			double x = v * cos(agl[i]) * t;
			if (sgn(x - wall[seq[lb + 1]].first) < 0) printf("%.6lf %.6lf\n", x, 0.0);
			else {
				t = wall[seq[lb + 1]].first / (v * cos(agl[i]));
				double y = v * sin(agl[i]) * t - 4.9 * t * t;
				printf("%.6lf %.6lf\n", wall[seq[lb + 1]].first, y);
			}
		}
	}
	return 0;
}
