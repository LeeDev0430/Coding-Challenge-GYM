#include <bits/stdc++.h>

using namespace std;
using DO = long double;

const DO eps = 1e-9,
	inf = 1e18;

struct point {
	DO x, y;
	point(DO x = 0, DO y = 0): x(x), y(y) {}
	point operator - (const point & a) const {
		return point(x - a.x, y - a.y);
	}
	DO operator * (const point & a) const {
		return x * x + y * y;
	}
	bool operator < (const point & a) const {
		return x < a.x;
	}
};

DO area(point a, point b, point c) {
	return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y);
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int n;
		cin >> n;
		point p[n];
		for (int a = 0; a < n; a++) {
			cin >> p[a].x >> p[a].y;
		}
		sort(p, p + n);
		vector < point > q;
		for (int a = 0; a < n; a++) {
			while (q.size() > 1) {
				if (area(q[q.size() - 2], q.back(), p[a]) < eps) {
					q.pop_back();
				} else {
					break;
				}
			}
			q.push_back(p[a]);
		}
		vector < point > v;
		for (int a = n - 1; a >= 0; a--) {
			while (v.size() > 1) {
				if (area(v[v.size() - 2], v.back(), p[a]) < eps) {
					v.pop_back();
				} else break;
			}
			v.push_back(p[a]);
		}
		for (int a = 1; a + 1 < v.size(); a++) {
			q.push_back(v[a]);
		}

		int m = q.size();
		DO d[m];
		for (int i = 0; i < m; i++) {
			d[i] = 0;
			point a = q[i], b = q[(i + 1) % m];
			point ve = {
				a.x - b.x,
				a.y - b.y
			};
			DO l = ve * ve;
			for (int j = 0; j < m; j++) {
				d[i] = max(d[i], abs(area(a, b, q[j])) / l);
			}
		}
		DO ans = inf;
		if (q.size() == 2) {
			ans = 0;
		}
		for (int i = 0; i < m; i++) {
			point a = {
				q[i].x - q[(i + 1) % m].x,
				q[i].y - q[(i + 1) % m].y
			};
			for (int j = i + 1; j < m; j++) {
				point b = {
					q[j].x - q[(j + 1) % m].x,
					q[j].y - q[(j + 1) % m].y
				};
				DO S = abs(area({
					0,
					0
				}, a, b));
				if (S > eps) {
					DO h = S / (b * b);
					DO l = d[j] * (a * a) / h;
					ans = min(ans, d[i] * l);
				}
			}
		}
		printf("Swarm %d Parallelogram Area: %.4lf\n", t, (double) ans);
	}
	return 0;
}