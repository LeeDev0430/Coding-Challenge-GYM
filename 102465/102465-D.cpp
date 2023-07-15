#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int mn[N], mx[N], _count[N];

int main() {
	int n, m, K;
	cin >> n >> m >> K;
	memset(mn, 0x3f, sizeof(mn));
	memset(mx, -1, sizeof(mx));
	for (int i = 1, x, y; i <= K; i ++) {
		scanf("%d %d", &x, &y);
		if(mn[x] > y) {
			mn[x] = y;
		}
		if(mx[x] < y) {
			mx[x] = y;
		}
	}
	long long cur_ans = 0;
	int cur_cnt = 0;
	for (int i = 0; i < n; i ++) {
		if (mx[i] != -1) {
			cur_ans += 2 * mx[i];
			cur_cnt --;
			_count[mn[i]]++;
			_count[mx[i]]++;
		}
	}
	long long ans = 1e18;
	for (int i = 0; i < m; i ++) {
		if(ans > cur_ans) {
			ans = cur_ans;
		}
		cur_cnt += _count[i];
		cur_ans += cur_cnt * 2;
	}
	cout << ans + n - 1 << endl;
	return 0;
}