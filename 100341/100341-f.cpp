#include<bits/stdc++.h>
using namespace std;
using VI = vector<int>;
 
VI solve() {
	char G; cin >> G;
	VI dp(4);
	if (G == 'g') {
		dp[0] = dp[3] = 0;
		dp[1] = dp[2] = 1;
	}
	else {
		VI Ldp = solve(), Rdp = solve();
		if (G == 'S') {
			dp[0] = max(Ldp[0] + Rdp[0], Ldp[1] + Rdp[2] - 1);
			dp[1] = max(Ldp[0] + Rdp[1], Ldp[1] + Rdp[3] - 1);
			dp[2] = max(Ldp[2] + Rdp[0], Ldp[3] + Rdp[2] - 1);
			dp[3] = max(Ldp[2] + Rdp[1], Ldp[3] + Rdp[3] - 1);
		}
		else {
			dp[0] = Ldp[0] + Rdp[0];
			dp[1] = Ldp[1] + Rdp[1] - 1;
			dp[2] = Ldp[2] + Rdp[2] - 1;
			dp[3] = Ldp[3] + Rdp[3] - 2;
		}
	}
	return dp;
}

int main() {
	freopen("independent.in", "r", stdin);
	freopen("independent.out", "w", stdout);
	VI dp = solve();
	int ans = 0;
	for(auto x : dp) {
		if(ans < x) {
			ans = x;
		}
	}
	cout << ans << endl;
	return 0;
}