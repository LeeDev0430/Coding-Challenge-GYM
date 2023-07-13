#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
using pii = pair<int, int>;
using VP  = vector<pii>;

const int N = 151, NN = 1e5;
const int M = 2e7, mod = 1e9 + 7;

int n, m, q, start_id;
int to[M], qq[N][N], dp[N][N];
vector<pii> qa[NN], qb[NN], qc[NN];
unsigned char X[M], Y[M];
bool grid[N][N];

void sum(int& x, const int &y) {
	x = x + y;
	if(x >= mod) {
		x -= mod;
	}
}

void calc(int x, int y) {
	memset(dp, 0, sizeof dp);
	dp[x][y] = 1;
	for (int i = x; i < n; ++i) {
		for (int j = y; j < m; ++j) {
			if (grid[i][j] && dp[i][j]) {
				sum(dp[i + 1][j], dp[i][j]);
				sum(dp[i][j + 1], dp[i][j]);
			}
		}
	}
	for (int i = qq[x][y]; i != -1; ) {
		int ians = 0;
		if(X[i] >= x && Y[i] >= y) {
			ians = dp[X[i]][Y[i]];
		}
		int inext = to[i];
		to[i] = ians;
		i = inext;
	}
}

void sum(const pii &p1, const pii &p2, int q) {
	X[q] = p2.x;
	Y[q] = p2.y;
	to[q] = qq[p1.x][p1.y];
	qq[p1.x][p1.y] = q;
}

void multi_vec(const VP &grid, const VP &b) {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			sum(grid[i], b[j], start_id++);
		}
	}
}

void in(vector<pii> &v) {
	int n;
	scanf("%d", &n);
	v.resize(n);
	for(auto &p : v) {
		scanf("%d %d", &p.x, &p.y);
		p.x --;
		p.y --;
	}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("turtle.in", "r", stdin);
	freopen("turtle.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			scanf(" %c", &c);
			grid[i][j] = (c == '.');
			qq[i][j] = -1;
		}
	}
	scanf("%d", &q);
	for (int t = 0; t < q; ++t) {
		in(qa[t]);
		in(qb[t]);
		in(qc[t]);
		multi_vec(qa[t], qc[t]);
		multi_vec(qa[t], qb[t]);
		multi_vec(qb[t], qc[t]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (grid[i][j]) {
				calc(i, j);
			}
		}
	}
	start_id = 0;
	for (int t = 0; t < q; ++t) {
		int ans = 0;
		int an = qa[t].size(), bn = qb[t].size(), cn = qc[t].size();
		for (int i = 0; i < an; ++i) {
			for (int k = 0; k < cn; ++k) {
				int x = to[start_id + i * cn + k];
				if (x) {
					for (int j = 0; j < bn; ++j) {
						int y = to[start_id + an * cn + i * bn + j];
						int z = to[start_id + an * cn + an * bn + j * cn + k];
						if((x - 1ll * y * z) % mod) {
							ans ++;
						}
					}
				}
			}
		}
		printf("%d\n", ans);
		start_id += an * cn + an * bn + bn * cn;
	}
	return 0;
}