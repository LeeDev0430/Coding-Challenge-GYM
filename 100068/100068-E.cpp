#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

int flag[N];
vector<int> adj[N];

int cnt, key;
void dfs(int u)
{
	cnt ++;
	flag[u] = 1;
	if(adj[u].size() == 1)
	{
		key = 0;
	}
	for(auto v : adj[u])
	{
		if(!flag[v])	
		{
			dfs(v);
		}
	}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("fortification.in", "r", stdin);
	freopen("fortification.out", "w", stdout);
#endif
	int n, m, ans = 1;
	cin >> n >> m;
	for(int i = 1; i <= m; i ++)
	{
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i = 1; i <= n; i ++)
	{
		if(!flag[i])
		{
			key = 1;
			cnt = 0;
			dfs(i);
			if(key)
			{
				ans = 1ll * ans * cnt % mod;
			}
		}
	}
	cout << ans << endl;
	return 0;
}