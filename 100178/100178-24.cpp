#include<bits/stdc++.h>

#define int INT
#define x first
#define y second

using namespace std;
using INT = long long;

const int N = 3.5e4 + 10;
const double eps = 1e-10;

int n, m, id;
int X, knight;
int MS[N];

struct circle {
	int x, y, r, c, u, id, cosin;
	double rr;
	circle(int x = 0, int y = 0, int r = 0, int c = 0, int u = 0, int id = 0, int cosin = 0, double rr = 0):
		x(x), y(y), r(r), c(c), u(u), id(id), cosin(cosin), rr(rr) {}
	bool operator < (const circle & b) const {
		double coa = y + u * sqrt(max(rr * rr - (double)(x - X) * (x - X), 0.0));
		double cob = b.y + b.u * sqrt(max(b.rr * b.rr - (double)(b.x - X) * (b.x - X), 0.0));
		return (fabs(coa - cob) > eps ? (coa < cob) : (u < b.u));
	}
}
T, B;

vector < circle > v;
set < circle > S;

vector < INT > g[N], d[N];
vector < INT > pe[N];
INT current, ans;
INT W[N], RA[N], NX[N], CO[N], SX;

set < pair < INT, int > > rst, st;

void go(int x, int f) {
	NX[x] = RA[x];
	for (int i = 0; i < g[x].size(); i++) {
		if (g[x][i] != f) {
			go(g[x][i], x), NX[x] += NX[g[x][i]];
		}
	}
}

void _erase(pair < INT, int > tr) {
	if (rst.find(tr) != rst.end()) {
		rst.erase(tr);
		current -= tr.x;
		return;
	}
	st.erase(tr);
}

void _insert(pair < INT, int > tr) {
	if (tr <= ( * st.begin())) {
		rst.insert(tr);
		current += tr.x;
	} else st.insert(tr);
	while (st.size() > knight) {
		rst.insert( * st.begin());
		current += ( * st.begin()).x;
		st.erase(st.begin());
	}
	while (st.size() < knight && rst.size()) {
		st.insert( * rst.rbegin());
		current -= ( * rst.rbegin()).x;
		rst.erase( * rst.rbegin());
	}
}

void dfs(int u, int f = 0) {
	id = u;
	ans = min(ans, current);
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i] != f) {
			pair < INT, int > tr = {
				NX[g[u][i]] * CO[g[u][i]],
				g[u][i]
			};
			_erase(tr);
			NX[g[u][i]] = SX - NX[g[u][i]];
			tr = {
				NX[g[u][i]] * CO[g[u][i]],
				g[u][i]
			};
			_insert(tr);
			ans = min(current, ans);
			dfs(g[u][i], u);
			_erase(tr);
			NX[g[u][i]] = SX - NX[g[u][i]];
			tr = {
				NX[g[u][i]] * CO[g[u][i]],
				g[u][i]
			};
			_insert(tr);
		}
	}
}

signed main() {
	#ifdef ONLINE_JUDGE
	freopen("camelot.dat", "r", stdin);
	freopen("camelot.sol", "w", stdout);
	#endif
	
	cin >> n >> m >> knight;
	for (int i = 1; i <= n; i++) {
		cin >> T.x >> T.y >> T.r >> T.c;
		T.id = i;
		CO[i] = T.c;
		T.cosin = T.x - T.r;
		v.push_back(T);
		T.cosin = T.x + T.r;
		v.push_back(T);
	}
	T.r = 0;
	for (int i = 1; i <= m; i++) {
		cin >> T.x >> T.y >> T.c;
		T.id = i;
		W[i] = T.c;
		T.cosin = T.x;
		v.push_back(T);
	}
	sort(v.begin(), v.end(), [ & ](const circle & a,
		const circle & b) {
		return a.cosin < b.cosin;
	});

	for (int i = 0; i < v.size(); i++) {
		X = v[i].cosin;
		if (v[i].cosin > v[i].x) {
			T = v[i];
			T.cosin = 0;
			T.u = 1;
			T.rr = (double) v[i].r - eps;
			S.erase(S.lower_bound(T));
			T.u = -1;
			T.rr = (double) v[i].r + eps;
			S.erase(S.lower_bound(T));
		} else if (v[i].cosin < v[i].x) {
			T = v[i];
			T.rr = T.r;
			T.u = -1;
			B = * S.lower_bound(T);
			if (B.u == -1) MS[T.id] = MS[B.id];
			else MS[T.id] = B.id;
			S.insert(T);
			T.u = 1;
			S.insert(T);
		} else {
			T = v[i];
			T.rr = T.r;
			B = * S.lower_bound(T);
			if (B.u == -1) RA[0] += W[T.id];
			else RA[B.id] += W[T.id];
		}
	}
	for (int i = 1; i <= n; i++) {
		pe[i].push_back(0);
		pe[MS[i]].push_back(0);
		g[i].push_back(MS[i]);
		g[MS[i]].push_back(i);
		d[i].push_back(RA[i]);
		d[MS[i]].push_back(RA[i]);
	}

	go(0, 0);

	for (int i = 0; i <= n; i++) {
		SX += RA[i];
	}

	for (int i = 1; i <= n; i++) {
		st.insert({
			NX[i] * CO[i],
			i
		});
	}

	while (st.size() > knight) {
		rst.insert( * st.begin());
		current += ( * st.begin()).x;
		st.erase(st.begin());
	}

	ans = current;
	dfs(0);
	cout << ans << endl;

	return 0;
}