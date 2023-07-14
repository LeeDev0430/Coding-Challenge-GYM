#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 20;
int n, m, k, root, ed = 1, sz = 1;
int deep[N], x[N], y[N], _in[N], _out[N], pos[N];
int par[N][M];
vector<int> adj[N];

void dfs(int v, int p = -1)
{
	x[v] = y[v] = ++ ed;
	for (auto i : adj[v])
	{
		if (i == p) continue;
		if (!x[i]) dfs(i, v);
		y[v] = min(y[v], y[i]);
	}
}

void calc(int v, int c, int par_c = 0)
{
	if (!_in[c])
	{
		par[c][0] = par_c;
		for (int i = 1; i < M; i++)
		{
			par[c][i] = par[par[c][i - 1]][i - 1];
		}
		_in[c] = ed;
		deep[c] = deep[par_c] + 1;
	}
	pos[v] = c;
	for (auto i : adj[v])
	{
		if (!pos[i])
		{
			calc(i, y[i] > x[v] ? ++sz : c, c);
		}
	}
	_out[c] = ed++;
}

bool is_anc(int a, int b)
{
	return _in[a] <= _in[b] && _out[a] >= _out[b];
}

int get_anc(int a, int b)
{
	if (is_anc(a, b)) return a;
	if (is_anc(b, a)) return b;
	for (int i = M - 1; i >= 0; i--)
	{
		if (par[a][i] && !is_anc(par[a][i], b))
		{
			a = par[a][i];
		}
	}
	return par[a][0];
}

int main()
{
#ifdef ONLINE_JUDGE
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
#endif
	scanf("%d %d %d", &n, &m, &root);
	
	for (int i = 0, u, v; i < m; i ++)
	{
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(root);
	calc(root, 1);
	
	cin >> k;
	for (int i = 0, u, v; i < k; i++)
	{
		scanf("%d %d", &u, &v);
		printf("%d\n", deep[get_anc(pos[u], pos[v])] - 1);
	}
	
	return 0;
}