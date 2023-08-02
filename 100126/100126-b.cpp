#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <limits>
#include <math.h>
#include <memory>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <numeric>
#include <cstring>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define max_n 10002

gp_hash_table < unsigned int, int> _hash[2];
int n[2], arr[2][max_n];
long long hid[2][max_n];
int frequency[max_n << 1];

int r = 137;

unsigned int pre_rands[max_n];

void precalc()
{
  pre_rands[0] = 1;
  for (int i = 1; i < max_n; i++)
  {
    pre_rands[i] = pre_rands[i - 1] *r;
  }

  pre_rands[0] = 0;
}

void get_hash(int i, int m)
{
  memset(frequency, 0, sizeof(frequency));
  long long cur_hash = 0, cur_hash2 = 0;
  for (int j = 1; j <= m; j++)
  {
    int x = frequency[arr[i][j]];
    frequency[arr[i][j]]++;
    cur_hash = cur_hash + pre_rands[x + 1] - pre_rands[x];
  }

  _hash[i][cur_hash] = 1;
  hid[i][1] = cur_hash;
  for (int j = m + 1; j <= n[i]; j++)
  {
    int x = frequency[arr[i][j - m]];
    cur_hash = cur_hash - pre_rands[x] + pre_rands[x - 1];
    frequency[arr[i][j - m]]--;
    x = frequency[arr[i][j]];
    cur_hash = cur_hash + pre_rands[x + 1] - pre_rands[x];
    frequency[arr[i][j]]++;
    _hash[i][cur_hash] = j - m + 1;
    hid[i][j - m + 1] = cur_hash;
  }
}

bool check_dop(int m, int &x, int &y)
{
  return hid[0][x] == hid[1][y];
}

bool is_ok(int m, int &x, int &y)
{
  _hash[0].clear();
  _hash[1].clear();
  get_hash(0, m);
  get_hash(1, m);
  for (auto a: _hash[0])
  {
    if (_hash[1].find(a.first) != _hash[1].end())
    {
      if (check_dop(m, a.second, _hash[1][a.first]))
      {
        x = a.second;
        y = _hash[1][a.first];
        return true;
      }
    }
  }

  return false;

}

set<int> total;
map<int, int> unique_values;

int main()
{
  freopen("freq.in", "r", stdin);
  freopen("freq.out", "w", stdout);

  ios::sync_with_stdio(0);
  cin.tie(0);

  precalc();

  for (int q = 0; q < 2; q++)
  {
    cin >> n[q];
    for (int i = 1; i <= n[q]; i++)
    {
      cin >> arr[q][i];
      total.insert(arr[q][i]);
    }
  }

  int t = 0;
  for (auto x: total)
  {
    unique_values[x] = t++;
  }

  for (int q = 0; q < 2; q++)
  {
    for (int i = 1; i <= n[q]; i++)
    {
      arr[q][i] = unique_values[arr[q][i]];
    }
  }

  int x = 1, y = 1;
  for (int m = min(n[0], n[1]); m >= 0; m--)
  {
    if (is_ok(m, x, y) == true)
    {
      cout << m << endl << x << " " << y;
      return 0;
    }
  }

  return 0;
}