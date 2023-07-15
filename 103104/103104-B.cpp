#include <bits/stdc++.h>
using namespace std;
using DO = double;

const int N = 1e5 + 10;
const DO eps = 1e-7;

struct Point {
	DO x, y;
	Point(DO x = 0, DO y = 0) : x(x), y(y) {}
	Point operator + (const Point &vec) const{ return {x + vec.x, y + vec.y}; }
	Point operator - (const Point &vec) const{ return {x - vec.x, y - vec.y}; }
	Point operator * (const DO &k) const{ return {k * x, k * y}; }
	DO len() const{ return sqrt(x * x + y * y); }
	Point unit() const{ return *this * (1 / len()); }
	Point rotate(const DO &t) const{ return {x * cos(t) - y * sin(t), y * cos(t) + x * sin(t)}; }
	bool operator < (const Point &vec) const{ return x < vec.x; }
};

Point p[N];

void Intersect(Point a, Point vec, Point &u, Point &v) {
	DO L = (vec - a).len();
	DO t = acos(max(-1.0, min(1.0, L / 4)));
	vec = (vec - a) * (2 / L);
	u = a + vec.rotate(t);
	v = a + vec.rotate(-t);
}

bool is_ok(Point w, vector<int> &vec, DO r, int j) {
	if(w.len() > r) {
		return false;
	}
	for(auto k : vec) {
		if(k != j && (p[k] - w).len() < 2 - eps) {
			return false;
		}
	}
	printf("Yes\n%.9lf %.9lf\n", w.x, w.y);
	return true;
};

void Solve() {
	int n; DO r;
	scanf("%d %lf", &n, &r);
	
	bool good = false;
	
	for(int i = 1; i <= n; i ++) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	
	sort(p + 1, p + n + 1);
	
	for(int L = 1, R = 1, i = 1; i <= n; i ++) {
		while(L < i && p[i].x - p[L].x > 4 + eps) L ++;
		while(R <= n && p[R].x - p[i].x < 4 + eps) R ++;
		vector<int> vec;
		for(int j = L; j < R; j ++) {
			if(j != i && (p[i] - p[j]).len() < 4 + eps) {
				vec.push_back(j);
			}
		}
		
		if(!vec.empty()) {
			good = true;
		}
		
		for(auto j : vec) {
			Point u, v;
			Intersect(p[i], p[j], u, v);
			if(is_ok(u, vec, r, j)) return;
			if(is_ok(v, vec, r, j)) return;
		}
	}

	if((n == 1 && 2 - p[1].len() <= r) || n > 1 && !good) {
		Point u = p[1] - p[1].unit() * 2;
		printf("Yes\n%.9lf %.9lf\n", u.x, u.y);
	}
	
	else {
		printf("No\n");
	}
}

int main() {
	Solve();
	return 0;
}