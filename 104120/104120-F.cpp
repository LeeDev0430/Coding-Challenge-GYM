#include<bits/stdc++.h>
#define md (l + r >> 1)
#define ls (u << 1)
#define rs (ls | 1)

using namespace std;


const int N = 2e5 + 10;

int a[N], b[N << 1];
int op, flag[N<<3];


struct seg{
	int mx, mn, ans;
	seg(int mx = -1e9, int mn = 1e9, int ans = 0) : mx(mx), mn(mn), ans(ans) {}
	seg operator + (const seg & a) {
		seg res = a;
		if(res.mx < mx) {
			res.mx = mx;
		}
		if(res.mn > mn) {
			res.mn = mn;
		}
		if(res.ans < ans) {
			res.ans = ans;
		}
		if(res.ans < a.mx - mn) {
			res.ans = a.mx - mn;
		}
		return res;
	}
};

seg bit[N][20], s[N << 2];

seg query(int l, int r) {
	if(l > r) {
		return seg();
	}
	int i = 31 - __builtin_clz(r - l + 1);
	seg res = bit[l][i] + bit[r - (1 << i) + 1][i];
	res.ans = max(bit[l][i].ans, bit[r - (1 << i) + 1][i].ans);
	return res;
}


void update(int p, int l, int r, int L) {
	int R = L + r - l, k = 31 - __builtin_clz(r - l + 1);
	flag[p] = L, s[p] = query(L, R);
	s[p].ans = max(s[p].ans, query(L + (1 << k), R).mx - query(L, R - (1 << k)).mn);
}



void push_down(int u,int l,int r,int m){
	if(flag[u]) {
		update(ls, l, m, flag[u]);
		update(rs, m + 1, r, flag[u] + m + 1 - l);
		flag[u] = 0;
	}
}


void build(int u, int l, int r){
	if(l == r) {
		s[u] = {a[l],a[l],0};
		return ;
	}
	build(ls, l, md);
	build(rs, md+1, r);
	s[u] = s[ls] + s[rs];
}

void change(int u, int l, int r, int L, int R, int p){
	if(L <= l && r <= R) {
		return update(u, l, r, p + l - L);
	}
	push_down(u, l, r, md);
	if(L <= md) {
		change(ls, l, md, L, R, p);
	}
	if(R > md) {
		change(rs, md + 1, r, L, R, p);
	}
	s[u] = s[ls] + s[rs];
}


seg calc(int u, int l, int r, int L, int R){
	if(L <= l && r <= R) {
		return s[u];
	}
	seg ans;
	push_down(u, l, r, md);
	if(L <= md) {
		ans = calc(ls, l, md, L, R);
	}
	if(R > md) {
		ans = ans + calc(rs, md + 1, r, L, R);
	}
	return ans;
}

int n;

int solve() {
	int op, l, r;
	scanf("%d %d %d", &op, &l, &r);
	if(op==1){
		int k;
		scanf("%d",&k);
		change(1, 1, n, l + 1, r + 1, k + 1);
		return s[1].ans;
	}
	else {
		return calc(1, 1, n, l + 1, r + 1).ans;
	}
}

int main(){
	int m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
	}
	for(int i = 1; i <= n; i ++) {
		scanf("%d", b + i);
		b[i + n] = b[i];
	}
	for(int j = 0; j < 20; j ++) {
		for(int i = 1; i <= n * 2; i ++) {
			if(j == 0) {
				bit[i][j] = seg(b[i], b[i], 0);
			}
			else {
				bit[i][j] = bit[i][j - 1] + bit[min(n * 2, i + (1 << j - 1))][j - 1];
			}
		}
	}
	build(1, 1, n);
	while(m --) {
		printf("%d\n", solve());
	}
	return 0;
} 