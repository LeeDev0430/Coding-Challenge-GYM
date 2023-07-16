#include <bits/stdc++.h>
using namespace std;
const int maxn = 220000;
int n, m, k, q, u, v, MX;
vector<int> son[maxn];
int cnt, sz[maxn], mx[maxn], del[maxn], fa[maxn], dep[maxn], dist[maxn];
int dis[50][maxn], qu[maxn], hd = 0, tl = 0, vis[maxn];
void bfs(int root, int s)
{
  qu[hd = tl = 1] = s;
  dis[root][s] = 0;
  while (hd <= tl)
  {
    int x = qu[hd++];
    for (auto t: son[x])
    {
      if (!dis[root][t] && !del[t] && t != s)
      {
        qu[++tl] = t;
        dis[root][t] = dis[root][x] + 1;
        vis[t] = 1;
      }
    }
  }
}

void dfs1(int x)
{
  sz[x] = 1;
  vis[x] = cnt;
  for (auto t: son[x])
  {
    if (!del[t] && vis[t] != cnt)
    {
      dfs1(t);
      sz[x] += sz[t];
    }
  }
}

void dfs2(int x, int fa, int lim)
{
  mx[x] = lim - sz[x];
  vis[x] = cnt;
  for (auto t: son[x])
  {
    if (!del[t] && vis[t] != cnt)
    {
      dfs2(t, x, lim);
      mx[x] = max(mx[x], sz[t]);
    }
  }

  if (mx[x] < mx[MX])
  {
    MX = x;
  }
}

void solve(int x, int ff)
{
  MX = 0;
  mx[0] = 1e9;
  ++cnt;
  dfs1(x);
  ++cnt;
  dfs2(x, 0, sz[x]);
  x = MX;
  del[x] = 1;
  fa[x] = ff;
  dep[x] = dep[ff] + 1;
  bfs(dep[x], x);
  for (auto t: son[x])
  {
    if (!del[t])
    {
      solve(t, x);
    }
  }
}

void modify(int x)
{
  for (int t = x; t; t = fa[t])
  {
    dist[t] = min(dist[t], dis[dep[t]][x]);
  }
}

int query(int x)
{
  int ans = 1e9;
  for (int t = x; t; t = fa[t])
  {
    ans = min(ans, dist[t] + dis[dep[t]][x]);
  }

  return ans;
}

int main()
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++)
  {
    scanf("%d%d", &u, &v);
    son[u].push_back(v);
    son[v].push_back(u);
  }

  for (int i = 1; i <= n; i++)
  {
    dist[i] = 1e9;
  }

  solve(1, 0);
  scanf("%d", &q);
  for (int i = 1; i <= q; i++)
  {
    int root, x;
    scanf("%d%d", &root, &x);
    if (root == 1)
      modify(x);
    else
    {
      printf("%d\n", query(x));
    }
  }

  return 0;
}