#include <bits/stdc++.h>
using namespace std;
typedef long long INT;

const int max_n = 1e7 + 10;

bitset<max_n> bits;

vector<INT> primes;

void pre_pare()
{
  for (int i = 3; i * i < max_n; i += 2)
  {
    if (!bits[i])
    {
      for (int j = i * i; j < max_n; j += i + i)
      {
        bits[j] = 1;
      }
    }
  }

  primes.push_back(2);
  for (int i = 3; i < max_n; i += 2)
  {
    if (!bits[i])
    {
      primes.push_back(i);
    }
  }
}

int main()
{
  pre_pare();
  int tcase;
  cin >> tcase;
  while (tcase--)
  {
    INT f, g;
    cin >> f >> g;
    INT res = 1ll, flag = 0;

    if (f % g)
    {
      flag = 1;
    }

    f /= g;
    if (f % g)
    {
      flag = 1;
    }

    f /= g;

    INT tp = 1ll;
    for (int i = 0; i < primes.size() && !flag; i++)
    {
      if (f % primes[i] == 0)
      {
        int c = 0;
        while (f % primes[i] == 0)
        {
          f /= primes[i];
          c++;
        }

        INT x = 3 + 3 *(c - 1);
        res *= x;
        if ((c & 1) == 0)
        {
          tp *= 2;
        }
      }
    }

    tp *= 3;

    if (f != 1)
    {
      res *= 3;
    }

    res -= tp;
    res /= 6ll;
    res += tp / 3ll;

    if (flag)
    {
      res = 0;
    }

    cout << res << endl;
  }

  return 0;
}