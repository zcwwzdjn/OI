#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100000;
int q;

struct Point {
	ll x, y;
	double agl;
	Point() {}
	Point(ll x_, ll y_) : x(x_), y(y_) {}
	int scan() {
		int res;
		scanf("%d%I64d%I64d", &res, &x, &y);
		return res;
	}
	void calc_agl() {
		agl = atan2(y, x);
	}
	bool operator < (const Point &t) const {
		return (agl < t.agl);
	}
} a, b, c, base;

set<Point> hull;

typedef Point Vector;
typedef set<Point>::iterator It;

Vector operator + (const Vector &a, const Vector &b) {
	return Vector(a.x + b.x, a.y + b.y);
}

Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y);
}

ll det(const Vector &a, const Vector &b) {
	return (a.x * b.y - b.x * a.y);
}

It Prev(It t) {
	if (t == hull.begin()) t = hull.end();
	return (-- t);
}

It Succ(It t) {
	++ t;
	if (t == hull.end()) t = hull.begin();
	return t;
}

bool Inside(const Point &p) {
	It it = hull.lower_bound(p);
	if (it == hull.end()) it = hull.begin();
	It succ = it, prev = Prev(it);
	return (det(p - (*prev), (*succ) - (*prev)) <= 0);
}

void Insert(const Point &p) {
	It it = hull.lower_bound(p);
	if (it == hull.end()) it = hull.begin();
	It succ = it, prev = Prev(it);
	while (true) {
		it = Prev(prev);
		if (det((*prev) - p, (*it) - p) < 0) break;
		hull.erase(prev);
		prev = it;
	}
	while (true) {
		it = Succ(succ);
		if (det((*succ) - p, (*it) - p) > 0) break;
		hull.erase(succ);
		succ = it;
	}
	hull.insert(p);
}

int main() {
	scanf("%d", &q);
	q -= 3;
	a.scan(), b.scan(), c.scan();
	base = Point(a.x + b.x + c.x, a.y + b.y + c.y);
	a.x *= 3, a.y *= 3, b.x *= 3, b.y *= 3, c.x *= 3, c.y *= 3;
	a = a - base, b = b - base, c = c - base;
	a.calc_agl(), b.calc_agl(), c.calc_agl();
	hull.insert(a), hull.insert(b), hull.insert(c);
	while (q --) {
		static int t;
		static Point p;
		t = p.scan();
		p.x *= 3, p.y *= 3, p = p - base;
		p.calc_agl();
		if (t == 1) {
			if (!Inside(p)) Insert(p);
		}
		else {
			if (Inside(p)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
