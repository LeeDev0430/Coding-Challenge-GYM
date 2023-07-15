#include <bits/stdc++.h>
using namespace std;
const int N = 1e4;

int C(int n) {
	return n * (n - 1) / 2;
}

vector<int> ans;

int main () {
	int x, y;
	scanf("%d %d", &x, &y);
	tie(x, y) = make_pair(x / __gcd(x, y), y / __gcd(x, y));
	if(y % 2 == 0) {
		puts("-1");
		return 0;
	}
	int n = y;
	while(n + 2 * y < N) {
		n += 2 * y;
	}
	int goal = x * n / y;
	int sum = 0, members = 0;
	while (members <= n) {
		int new_team = 1;
		while(C(new_team) + sum <= goal) new_team ++;
		new_team --;
		ans.push_back(new_team);
		members += new_team;
		sum += C(new_team);
	}
	printf("%d\n", ans.size());
	for(int i = 0; i < ans.size(); i ++) {
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	}
	return 0;
}