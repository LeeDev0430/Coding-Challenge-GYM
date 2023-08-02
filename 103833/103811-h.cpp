#include <set>
#include <map>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <math.h>
#include <memory>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <bitset>
#include <stdio.h>
#include <numeric>
#include <cstring>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <algorithm>
using namespace std;

int n, C;
long long P;
vector<int> c;
vector < long long > p;

void smax(long long &x, const long long &y)
{
  (x < y) && (x = y);
}

struct Queue
{
  stack<int> in ;
  vector<vector < long long>> dp1, dp2;

  void add(vector<vector < long long>> &dp, int i)
  {
    vector < long long > new_dp(C + 1, -3e18);
    new_dp[0] = 0;
    if (dp.empty())
    {
      smax(new_dp[c[i]], p[i]);
      dp.push_back(new_dp);
      return;
    }

    new_dp = dp.back();
    for (int x = 0; x <= C; x++)
    {
      if (x + c[i] > C)
      {
        break;
      }

      smax(new_dp[x + c[i]], dp.back()[x] + p[i]);
    }

    dp.push_back(new_dp);
  }

  void push(int i)
  {
    add(dp1, i); in .push(i);
  }

  void pop()
  {
    if (dp2.empty())
    {
      while (! in .empty())
      {
        add(dp2, in .top());
        dp1.pop_back(); in .pop();
      }
    }

    dp2.pop_back();
  }

  long long check()
  {
    if (dp1.empty() && dp2.empty())
    {
      return 0;
    }

    if (dp2.empty())
    {
      long long res = 0;
      for (int i = 0; i <= C; i++)
      {
        res = max(res, dp1.back()[i]);
      }

      return res;
    }

    if (dp1.empty())
    {
      long long res = 0;
      for (int i = 0; i <= C; i++)
      {
        res = max(res, dp2.back()[i]);
      }

      return res;
    }

    vector < long long > pref(C + 1);
    pref[0] = dp2.back()[0];
    for (int i = 1; i <= C; i++)
    {
      pref[i] = max(pref[i - 1], dp2.back()[i]);
    }

    long long res = 0;
    for (int i = 0; i <= C; i++)
    {
      res = max(res, dp1.back()[i] + pref[C - i]);
    }

    return res;
  }
};

void solve()
{
  long long P;
  cin >> n >> C >> P;
  c.resize(n);
  for (int &i: c)
  {
    cin >> i;
  }

  p.resize(n);
  for (long long &i: p)
  {
    cin >> i;
  }

  Queue que;
  for (int l = 0, r = 0; l < n; l++)
  {
    while (r < n && que.check() < P)
    {
      que.push(r++);
    }

    if (l)
    {
      cout << " ";
    }

    if (que.check() >= P)
    {
      cout << r;
    }
    else
    {
      cout << "-1";
    }

    que.pop();
  }

  cout << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

//  freopen("in.txt", "r", stdin);

  solve();

  return 0;
}