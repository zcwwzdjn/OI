/*
 * $File: pre.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given the length of arc and the
 *   corresponding chord, calculate the
 *   height.
 *
 * Solution:
 *   Binary search the angle and check.
 */

#include <cmath>
#include <cstdio>

const double kPi = acos(-1.0);
int n, l, d;

int Solve(int a, int b) {
	double lb = 0.0, rb = kPi;
	for (int t = 0; t < 50; ++ t) {
		double mid = (lb + rb) * 0.5;
		double r = a / (2.0 * sin(mid * 0.5));
		double l = r * mid;
		if (l < b) lb = mid;
		else rb = mid;
	}
	double r = a / (2.0 * sin(rb * 0.5));
	double res = r - r * cos(rb * 0.5);
	return (int)(res + 0.5);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &l, &d);
		printf("%d\n", Solve(l, l + d));
	}
	return 0;
}
