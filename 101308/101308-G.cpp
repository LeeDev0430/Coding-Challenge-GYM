#include <bits/stdc++.h>
using namespace std;

const int N = 333,
  M = N *N,
  P = 100000;

int r, c, n, m, len, rem;
int digit[N], id[N][N], grid[N][N], ans[M], pos[M][2];
char pavel[N][N], d[N];

struct permutation
{
  int y[M], x[M];
  permutation operator*(const permutation &p)
  {
    permutation res;
    for (int i = 1; i <= n; i++)
    {
      res.y[i] = p.y[y[i]];
      res.x[i] = (x[i] + p.x[y[i]]) % P;
    }

    return res;
  }
}

x, y;

void _rotate(int x, int y, char op)
{
  ans[grid[x][y]]++;
  if (op == 'N') return;
  if (op == 'L')
  {
    swap(grid[x + 1][y], grid[x][y]);
    swap(grid[x][y], grid[x][y + 1]);
    swap(grid[x][y + 1], grid[x + 1][y + 1]);
  }

  if (op == 'R')
  {
    swap(grid[x][y], grid[x][y + 1]);
    swap(grid[x + 1][y], grid[x][y]);
    swap(grid[x + 1][y + 1], grid[x + 1][y]);
  }
}

int main()
{
  #ifdef ONLINE_JUDGE
  freopen("garbling.in", "r", stdin);
  freopen("garbling.out", "w", stdout);
  #endif

  scanf("%d%d%s", &r, &c, d + 1);
  len = strlen(d + 1);
  for (int i = len; i; i--)
  {
    digit[len - i + 1] = d[i] - '0';
  }

  for (int i = 1; i <= r; i++)
  {
    for (int j = 1; j <= c; j++)
    {
      id[i][j] = grid[i][j] = ++n;
      pos[n][0] = i;
      pos[n][1] = j;
    }
  }

  m = (r - 1) *(c - 1);
  for (int i = 1; i < r; i++)
  {
    scanf("%s", pavel[i] + 1);
    for (int j = 1; j < c; j++)
    {
      _rotate(i, j, pavel[i][j]);
    }
  }

  for (int i = 1; i <= r; i++)
  {
    for (int j = 1; j <= c; j++)
    {
      x.y[grid[i][j]] = id[i][j];
    }
  }

  for (int i = 1; i <= n; i++)
  {
    y.y[i] = i;
    x.x[i] = ans[i];
  }

  for (int i = len; i; i--)
  {
    rem = (rem *10 + digit[i]) % m;
  }

  for (int i = len; i; i--)
  {
    digit[i - 1] += digit[i] % m * 10;
    digit[i] /= m;
  }

  while (len && !digit[len])
  {
    len--;
  }

  while (len)
  {
    if (digit[1] &1)
    {
      y = y * x;
    }

    for (int i = len; i; i--)
    {
      digit[i - 1] += digit[i] % 2 * 10;
      digit[i] /= 2;
    }

    while (len && !digit[len])
    {
      len--;
    }

    x = x * x;
  }

  for (int i = 1; i <= n; i++)
  {
    grid[pos[y.y[i]][0]][pos[y.y[i]][1]] = i;
    ans[i] = y.x[i];
  }

  for (int i = 1; i < r; i++)
  {
    for (int j = 1; j < c; j++)
    {
      if (rem > 0)
      {
        _rotate(i, j, pavel[i][j]);
        rem--;
      }
    }
  }

  for (int i = 1; i <= n; i++)
  {
    printf("%d\n", ans[i] % P);
  }

  return 0;
}