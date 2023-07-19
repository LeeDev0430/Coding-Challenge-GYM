#include <bits/stdc++.h>

using namespace std;

const int max_n = 1e3 + 10;

int n, info_n, ans_n;
int sits[11][5];
int a[max_n], len[max_n];
int tmp[max_n], max_ans;
int human[max_n][max_n];
pair < int, int > info[max_n], ans[max_n];

void update() {
  int k = 0;
  for (int i = 1; i <= info_n; i++) {
    if (info[i].first == 2) {
      k++;
    }
  }
  if ((k + 1) / 2 + (info_n - k) > 9) {
    return;
  }
  int now = 0;
  for (int i = 1; i <= info_n; i++) {
    now += info[i].first * (info[i].first - 1) * a[info[i].second];
  }
  if (now > max_ans) {
    max_ans = now;
    ans_n = info_n;
    for (int i = 1; i <= info_n; i++) {
      ans[i] = info[i];
    }
  }
}

void dfs(int i, int k) {
  if (i > n) {
    update();
    return;
  }
  dfs(i + 1, 0);
  for (int j = 2; j + k <= len[i]; j++) {
    info[++info_n].second = i;
    info[info_n].first = j;
    dfs(i + (j + k) / len[i], (j + k) % len[i]);
    info_n--;
  }
}

void print() {
  printf("%d\n", max_ans);
  for (int i = 1; i <= ans_n; i++) {
    for (int j = 1; j <= 9; j++) {
      if (tmp[j] + ans[i].first <= 4) {
        for (int k = 1; k <= ans[i].first; k++) {
          sits[j][++tmp[j]] = human[ans[i].second][len[ans[i].second]--];
        }
        break;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 9; j++) {
      while (tmp[j] < 4 && len[i]) {
        sits[j][++tmp[j]] = human[i][len[i]--];
      }
    }
  }
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 4; j++) {
      printf("%d%c", sits[i][j], j == 4 ? '\n' : ' ');
    }
  }
}

int main() {
  freopen("tickets.in", "r", stdin);
  freopen("tickets.out", "w", stdout);
  scanf("%d", & n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", & len[i], & a[i]);
    for (int j = 1; j <= len[i]; j++) {
      scanf("%d", & human[i][j]);
    }
  }
  dfs(1, 0);
  print();
  return 0;
}