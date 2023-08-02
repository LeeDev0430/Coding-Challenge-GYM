#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <math.h>
using namespace std;

const int max_n = 555;
const int mod = 37493;

int stirling1[max_n][max_n];
int sum_of_stirling1[max_n];
int splits[max_n][max_n];
vector<int> adj[max_n];
int dyna[max_n][max_n];
vector<int> cycle;
int deep[max_n];

void dfs(int u, int father = -1, int depth = 1)
{
  deep[u] = depth;
  for (int v: adj[u])
  {
    if (v == father)
      continue;
    if (deep[v] == 0)
    {
      dfs(v, u, depth + 1);
    }
    else if (deep[v] < deep[u])
    {
      cycle.push_back(deep[u] - deep[v] + 1);
    }
  }
}

int solve(int n, int number_of_lumps)
{
  for (int i = 1; i <= n; i++)
  {
    dyna[0][i] = splits[i][number_of_lumps];
  }

  for (int i = 0; i < cycle.size(); i++)
  {
    for (int j = 1; j <= n; j++)
    {
      dyna[i + 1][j] = (dyna[i][j] - dyna[i][j - 1] + mod) % mod;
    }

    for (int j = 3; j < cycle[i]; j++)
    {
      for (int k = n; k >= 1; k--)
      {
        dyna[i + 1][k] = (dyna[i][k] - dyna[i + 1][k - 1] + mod) % mod;
      }
    }
  }

  printf("%d\n", dyna[cycle.size()][n]);
}

int main()
{
  freopen("codecircles.in", "r", stdin);
  freopen("codecircles.out", "w", stdout);
  for (int i = 1; i < max_n; i++)
  {
    stirling1[i][1] = 1;
    for (int j = 2; j < i; j++)
    {
      stirling1[i][j] = (stirling1[i - 1][j - 1] + stirling1[i - 1][j] *j) % mod;
    }

    stirling1[i][i] = 1;
    sum_of_stirling1[i] = accumulate(stirling1[i] + 1, stirling1[i] + i + 1, 0) % mod;
  }

  for (int i = 1; i < max_n; i++)
  {
    splits[i][i] = sum_of_stirling1[i];
    for (int j = i - 1; j >= 1; j--)
    {
      splits[i][j] = (splits[i][j + 1] - splits[i - 1][j] + mod) % mod;
    }
  }

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int number_of_lumps = 0;
  for (int i = 0; i < n; i++)
  {
    if (deep[i] == 0)
    {
      number_of_lumps++;
      dfs(i);
    }
  }

  solve(n, number_of_lumps);
  return 0;
}