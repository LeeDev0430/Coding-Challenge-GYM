#include "bits/stdc++.h"
#define ls (u << 1)
#define rs (ls | 1)
#define md (l+r>>1)
using namespace std;

const int N = 2.5e5 + 10;

static const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
static const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct term{
	int x, y, v, k, len;
};

struct Point{
	int x, y, v;
	term getLine(int dir, int len) {
		switch(dir) {
			case 0:
				return term{x, y, v, 1, len};
			case 4:
				return term{x-len+1, y, v, 1, len};
			case 2:
				return term{x, y, v, 2, len};
			case 6:
				return term{x, y-len+1, v, 2, len};
			case 1:
				return term{x, y, v, 3, len};
			case 5:
				return term{x-len+1, y-len+1, v, 3, len};
			case 3:
				return term{x, y, v, 4, len};
			case 7:
				return term{x+len-1, y-len+1, v, 4, len};
		}
	}
} pnt[N<<2];



term stk[N * 10];
term p[N * 10];
int cnt, top;

struct segmentTree{
	long long total[N << 2];
	long long flag[N << 2];
	
	void init(){
		memset(total, 0, sizeof(total));
		memset(flag, 0, sizeof(flag));
	}
	
	void pushup(int u){
		total[u] = total[ls] + total[rs];
	}
	
	void update(int u, int len, int v){
		total[u] += (long long) len * v;
		flag[u] += v;
	}
	
	void pushdown(int u, int l, int r){
		if(flag[u]){
			update(ls, md - l + 1, flag[u]);
			update(rs, r - md, flag[u]);
			flag[u] = 0;
		}
	}
	
	void change(int u, int l, int r, int L, int R, int v){
		if(L <= l && r <= R){
			update(u, r - l + 1, v);
			return;
		}
		pushdown(u, l, r);
		if(L <= md) {
			change(ls, l, md, L, R, v);
		}
		if(R > md) {
			change(rs, md + 1, r, L, R, v);
		}
		pushup(u);
	}
	
	long long get(int u, int l, int r, int L, int R){
		if(L <= l && r <= R) {
			return total[u];
		}
		pushdown(u, l, r);
		if(R <= md) {
			return get(ls, l, md, L, R);
		}
		if(L > md) {
			return get(rs, md + 1, r, L, R);
		}
		return get(ls, l, md, L, R) + get(rs, md + 1, r, L, R);
	}
	
	void change(int L, int R, int v){
		if(L <= R) {
			change(1, 0, N, L, R, v);
		}
	}
	
	long long get(int L, int R){
		if(L <= R) {
			return get(1, 0, N, L, R);
		}
		return 0;
	}
};

segmentTree X, Y;

long long res[N];

void calc(int typ) {
	X.init();
	Y.init();
	top = 0;
	
	for(int i = 1; i <= cnt; i ++) {
		if(p[i].v > 1 || p[i].k == typ) {
			stk[++ top] = p[i];
		}
	}
	
	switch(typ) {
		case 1: {
			sort(stk + 1, stk + top + 1, [](const term a, const term b){
				return a.y != b.y ? a.y < b.y : a.v < b.v;
			});
			for(int i = 1; i <= top; i ++) {
				if(stk[i].v <= 1) {
					X.change(stk[i].x, stk[i].x + stk[i].len - 1, stk[i].v);
				}
				else {
					res[stk[i].v - 1] += X.get(0, stk[i].x);
				}
			}
			break;
		}
		case 2: {
			sort(stk + 1, stk + top + 1, [](const term a, const term b){
				return a.x != b.x ? a.x < b.x : a.v < b.v;
			});
			for(int i = 1; i <= top; i ++)
				if(stk[i].v <= 1) {
					Y.change(stk[i].y, stk[i].y + stk[i].len - 1, stk[i].v);
				}
				else {
					res[stk[i].v - 1] += Y.get(0, stk[i].y);
				}
			break;
		}
		case 3: {
			sort(stk + 1, stk + top + 1, [](const term a, const term b){
				return a.y - a.x != b.y - b.x ? a.y - a.x < b.y - b.x : a.v < b.v;
			});
			for(int i = 1; i <= top; i ++) {
				if(stk[i].v <= 1) {
					X.change(stk[i].x, stk[i].x + stk[i].len - 1, stk[i].v);
				}
				else {
					res[stk[i].v - 1] += X.get(0, stk[i].x);
				}
			}
			for(int i = top; i >= 1; i --) {
				if(stk[i].v <= 1) {
					Y.change(stk[i].y, stk[i].y + stk[i].len - 1, stk[i].v);
				}
				else {
					res[stk[i].v - 1] += Y.get(0, stk[i].y);
				}
			}
			break;
		}
		case 4: {
			sort(stk + 1, stk + top + 1, [](const term a, const term b){
				return a.x + a.y != b.x + b.y ? a.x + a.y < b.x + b.y : a.v < b.v;
			});
			long long total=0;
			for(int i = 1; i <= top; i ++) {
				if(stk[i].v <= 1){
					X.change(stk[i].x - stk[i].len + 1, stk[i].x, stk[i].v);
					Y.change(stk[i].y, stk[i].y + stk[i].len - 1, stk[i].v);
					total += stk[i].len * stk[i].v;
				}
				else {
					res[stk[i].v - 1] += total - X.get(stk[i].x + 1, N) - Y.get(stk[i].y + 1, N);
				}
			}
			break;
		}
	}
}

int main(){
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	
	for(int i = 1, k = 0; i <= n; i ++){
		int st_x, st_y, ed_x, ed_y;
		scanf("%d %d %d %d", &st_x, &st_y, &ed_x, &ed_y);
		ed_x++, ed_y++;
		pnt[++ k] = Point{st_x, st_y, 1};
		pnt[++ k] = Point{st_x, ed_y, -1};
		pnt[++ k] = Point{ed_x, st_y, -1};
		pnt[++ k] = Point{ed_x, ed_y, 1};
	}
	
	for(int i = 1; i <= m; i ++){
		int d, id, L, k;
		scanf("%d %d %d", &d, &id, &L);
		for(int j = 0, k = (id - 1) << 2 | 1; j < 4; j ++) {
			p[++ cnt] = pnt[k + j].getLine(d, L);
			pnt[k + j].x += dx[d] * L;
			pnt[k + j].y += dy[d] * L;
		}
	}
	
	for(int i = 1; i <= (n << 2); i ++) {
		p[++ cnt] = term{pnt[i].x, pnt[i].y, pnt[i].v, 1, 1};
	}
	
	for(int i = 1, x, y; i <= q; i ++){
		scanf("%d %d", &x, &y);
		p[++ cnt] = term{x, y, i + 1, 0, 0};
	}
	
	for(int i = 1; i <= 4; i ++) {
		calc(i);
	}
	
	for(int i = 1; i <= q; i ++) {
		printf("%I64d\n", res[i]);
	}
	return 0;
}