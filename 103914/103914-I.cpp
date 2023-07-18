#include <bits/stdc++.h>
#define ls(_)((_) << 1)
#define rs(_)(ls(_) | 1)
using namespace std;
mt19937_64 rnd(time(0));

const int max_n = 1e5 + 10;

int N, n, m, edge_n;
unsigned long long weight[max_n];
map<pair<int, int>, int> ma;
pair<int, int> edge[max_n + max_n];
vector<array<int, 3>> turpl[max_n];
vector<int> rem[max_n + max_n];
int dfs_array[max_n], times, L[max_n], R[max_n];
int question_id[max_n];

struct DSU
{
  int fa[max_n], sz[max_n];
  unsigned long long Ha, ha[max_n];
  pair<int, int> stk[max_n + max_n];
  int top;
  void init()
  {
    Ha = 0;
    top = 0;
    for (int i = 1; i <= n; i++)
    {
      fa[i] = i;
      sz[i] = 1;
      ha[i] = weight[i];
      Ha += weight[i];
    }
  }

  int find(int x)
  {
    if (fa[x] == x)
    {
      return x;
    }

    return find(fa[x]);
  }

  void merge(int x, int y)
  {
    int xx = find(x);
    int yy = find(y);
    if (sz[xx] > sz[yy])
    {
      swap(xx, yy);
    }

    if (xx == yy)
    {
      stk[++top] = { -1, -1 };

      return;
    }

    stk[++top] = { xx, yy
    };

    Ha -= ha[xx];
    Ha -= ha[yy];
    fa[xx] = yy;
    sz[yy] += sz[xx];
    ha[yy] ^= ha[xx];
    Ha += ha[yy];
  }

  void split()
  {
    int x = stk[top].first;
    int y = stk[top].second;
    top--;
    if (x == -1)
    {
      return;
    }

    Ha -= ha[y];
    fa[x] = x;
    sz[y] -= sz[x];
    ha[y] ^= ha[x];
    Ha += ha[x];
    Ha += ha[y];
  }
}

dsu;
void add_e(int u, int v)
{
  if (!ma[
    {
      u, v
    }])
  {
    ma[
    {
      u, v
    }] = ++edge_n;
    edge[edge_n] = { u, v
    };

    rem[edge_n].clear();
  }
}

void pre_dfs(int u)
{
  dfs_array[u] = ++times;
  L[u] = dfs_array[u];
  for (int i = 0; i < turpl[u].size(); i++)
  {
    int v = turpl[u][i][0];
    pre_dfs(v);
    rem[turpl[u][i][2]].push_back(L[v]);
    rem[turpl[u][i][2]].push_back(R[v] + 1);
  }

  R[u] = times;
}

vector<int> is_in[max_n *4];
unsigned long long ans[max_n];

void attach(int id, int l, int r, int x, int y, int v)
{
  if (x <= l && r <= y)
  {
    is_in[id].push_back(v);
    return;
  }

  int mid = (l + r) >> 1;
  if (x <= mid)
  {
    attach(ls(id), l, mid, x, y, v);
  }

  if (y > mid)
  {
    attach(rs(id), mid + 1, r, x, y, v);
  }
}

void dfs(int id, int l, int r)
{
  for (int i = 0; i < is_in[id].size(); i++)
  {
    dsu.merge(edge[is_in[id][i]].first, edge[is_in[id][i]].second);
  }

  int mid = (l + r) >> 1;
  if (l == r)
  {
    ans[question_id[l]] = dsu.Ha;
  }
  else
  {
    dfs(ls(id), l, mid);
    dfs(rs(id), mid + 1, r);
  }

  for (int i = 0; i < is_in[id].size(); i++)
  {
    dsu.split();
  }
}

void solution()
{
  scanf("%d%d%d", &N, &n, &m);
  for (int i = 1; i <= m; i++)
  {
    turpl[i].clear();
  }

  for (int i = 1; i <= n; i++)
  {
    weight[i] = rnd();
  }

  ma.clear();
  times = edge_n = 0;
  for (int i = 1; i <= N; i++)
  {
    turpl[i].clear();
  }

  for (int i = 1; i <= 4 * N; i++)
  {
    is_in[i].clear();
  }

  for (int i = 1; i <= m; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    add_e(u, v);
    rem[i].push_back(1);
    rem[i].push_back(N + 1);
  }

  for (int i = 2; i <= N; i++)
  {
    int p, u, v;
    string s;
    scanf("%d", &p);
    cin >> s;
    scanf("%d%d", &u, &v);
    add_e(u, v);
    if (s[0] == 'a')
    {
      turpl[p].push_back({ i, 1, ma[
        {
          u, v
        }] });
    }
    else
    {
      turpl[p].push_back({ i, -1, ma[
        {
          u, v
        }] });
    }
  }

  pre_dfs(1);
  for (int i = 1; i <= N; i++)
  {
    question_id[dfs_array[i]] = i;
  }

  for (int i = 1; i <= edge_n; i++)
  {
    sort(rem[i].begin(), rem[i].end());
    for (int j = 0; j < rem[i].size(); j += 2)
    {
      int l = rem[i][j];
      int r = rem[i][j + 1] - 1;
      if (l <= r)
      {
        attach(1, 1, N, l, r, i);
      }
    }
  }

  dsu.init();
  dfs(1, 1, N);
  vector<pair < unsigned long long, int>> vec;
  vec.clear();
  for (int i = 1; i <= N; i++)
  {
    vec.push_back({ ans[i], i });
  }

  sort(vec.begin(), vec.end());
  int ans1 = 1;
  for (int i = 0; i + 1 < vec.size(); i++)
  {
    if (vec[i].first != vec[i + 1].first)
    {
      ans1++;
    }
  }

  printf("%d\n", ans1);
  for (int i = 0; i < vec.size(); i++)
  {
    int j = i;
    while (j < vec.size() && vec[j].first == vec[i].first)
    {
      j++;
    }

    j--;
    printf("%d ", j - i + 1);
    for (int l = i; l <= j; l++)
    {
      printf("%d ", vec[l].second);
    }

    putchar('\n');
    i = j;
  }
}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  #endif

  int tcase = 1;
  cin >> tcase;
  while (tcase--)
  {
    solution();
  }

  return 0;
}