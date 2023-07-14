#include <bits/stdc++.h>
using namespace std;
using DO = long double;

const int NN  = 1e3 + 10;
const DO  pi  = acos(-1);
const DO  eps = 1e-16;

struct point {
	DO x, y;
	point (DO x = 0, DO y = 0) : x(x), y(y) {}
	point operator + (point a) {return point(x + a.x, y + a.y);}
	point operator - (point a) {return point(x - a.x, y - a.y);}
	point operator / (DO a) {return point(x / a, y / a);}
	point operator * (DO a) {return point(x * a, y * a);}
	DO operator ^ (point a) {return x * a.y - y * a.x;}
	DO operator & (point a) {return x * a.x + y * a.y;}
	DO len() {return sqrt(x * x + y * y);}
	point conj() {return point(-y, x);}
} T[NN];

int n, a, b, c;

bool straight(point a, point b, point c) {
	return fabs((a - b).len() + (a - c).len() - (b - c).len()) < eps;
}

point pa, pb;

bool intersect(point cp, DO r, point st, point en) {
	DO len = (en - st).len();
	DO d = fabs(cp - st ^ en - st) / len;
	if (d >= r) return 0;
	DO dx =sqrt(r * r - d * d);
	DO x = (cp - st & en - st) / len;
	DO a = (x - dx) / len, b = (x + dx) / len;
	pa = st * (1 - a) + en * a;
	pb = st * (1 - b) + en * b;
	return 1;
}

point p[NN], cr[3];

int cycle_intersection(point c, DO r, point cc, DO rr) {
	DO d = (c - cc).len();
	if (r + rr < d - eps || r + d < rr - eps || rr + d < r - eps) return 0;
	DO x = (r * r - rr * rr + d * d) / (d * 2);
	point cp = (c * (d - x) + cc * x) / d;
	DO h = sqrt(r * r - x * x);
	point dv = (cc - c).conj() * h / d ;
	cr[0] = cp - dv;
	cr[1] = cp + dv;
	return 1;
}

int is_in_polygon(point *p, point q, int n) {
	int cnt = 0;
	for (int i = 0; i < n; i ++) {
		int j = (i + 1) % n;
		if (straight(q, p[i], p[j])) return 1;
		if (p[j].y > q.y && p[i].y <= q.y ||
			p[i].y > q.y && p[j].y <= q.y) {
			DO x = (p[j] - q ^ p[i] - q) * (p[i].y - p[j].y);
			if (x > eps) cnt ++;
		}
	}
	return cnt & 1;
}

bool can(DO R, int a, int b, int c) {
	for (int i = 0; i < n; i++) {
		T[i] = point(R * cos(2 * pi / n * i), R * sin(2 * pi / n * i));
	}
	T[n] = T[0];
	int m = 0;
	for (int j = 0; j < n; j++) {
		if (intersect(T[0], a, T[j], T[j+1])) {
			if (straight(pa, T[j], T[j+1])) p[m++] = pa;
			if (straight(pb, T[j], T[j+1])) p[m++] = pb;
		}
	}
	for (int i = 0; i < m; i++) {
		if (cycle_intersection(T[0], b, p[i], c)) {
			if (is_in_polygon(T, cr[0], n) || is_in_polygon(T, cr[1], n)) return 1;
		}
		if (cycle_intersection(T[0], c, p[i], b)) {
			if (is_in_polygon(T, cr[0], n) || is_in_polygon(T, cr[1], n)) return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d %d %d %d", &n, &a, &b, &c);
	DO st = 0, ed = 100, md;
	for(int i = 0; i < 30; i ++) {
		md = (st + ed) / 2;
		(can(md, a, b, c) || can(md, b, a, c) || can(md, c, a, b)) ? (ed = md) : (st = md);
	}
	cout << setprecision(12) << n * st * st * sin(2 * pi / n) / 2 << endl;
	return 0;
}