#include "bits/stdc++.h"

using namespace std;

struct point {
	int x, y;
	
	point(int x = 0, int y = 0) : x(x), y(y) {}
	
	point operator - (const point & p) {
		return point(x - p.x, y - p.y);
	}
	
	int operator ^ (const point & p) {
		return x * p.y - y * p.x;
	}
	
	int len2() {
		return x * x + y * y;
	}
	
	double angle() {
		return atan2(y, x);
	}
	
	void input() {
		scanf("%d %d", &x, &y);
	}
};

struct segment{
	int x, y;
	double ang;
	
	segment(int x = 0, int y = 0, double ang = 0) : x(x), y(y), ang(ang) {}
	
	bool operator < (const segment & e) {
		return ang < e.ang;
	}
};


const int N = 555;
const double inf = 1e20, eps = 1e-9;

int n, m;
int ids[N];
segment seg[N * N];
double dp[N];
point p[N];

bool ok(int pivot, double mid) {
	for(int i = 0; i < n; i ++) {
		dp[i] = i == pivot ? 0 : - inf;
	}
	
	for(int i = 0; i < m; i ++) {
		dp[seg[i].y] = max(dp[seg[i].y], dp[seg[i].x] + (p[seg[i].x] ^ p[seg[i].y]) - mid * (p[seg[i].y] - p[seg[i].x]).len2());
	}
	
	return dp[pivot] > 0;
}

int main(){
	srand(time(0));
	
	int T; cin >> T;
	
	while(T --) {
		scanf("%d", &n);
		
		for(int i = 0; i < n; i ++) {
			p[i].input();
		}
		
		m = 0;
		
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++) {
				if(i != j) {
					seg[m ++] = segment(i, j, (p[j] - p[i]).angle());
				}
			}
		}
		
		sort(seg, seg + m);
		
		for(int i = 0; i < n; i ++) {
			ids[i] = i;
		}
		
		random_shuffle(ids, ids + n);
		
		double st = 0;
		
		for(int i = 0; i < n; i ++) {
			if(ok(ids[i], st + max(st, 1.0) * eps)) {
				double ed = 100;
				for(int step = 50; step > 0 && ed - st > max(st, 1.0) * eps; step --) {
					double md = (st + ed) / 2;
					if(ok(ids[i], md)) {
						st = md;
					}
					else {
						ed = md;
					}
				}
			}
		}
		
		printf("%.15f\n", st / 2);
	}
	return 0;
}