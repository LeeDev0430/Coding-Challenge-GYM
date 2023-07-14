#include <bits/stdc++.h>

using namespace std;
using UINT = unsigned long long;

int n, x;

UINT rd() {
	UINT ans = 0;
	for(int i = 0, d; i < x; i ++) {
		if(i == 0) {
			scanf("%d", &d);
		}
		else {
			scanf(".%d", &d);
		}
		ans = ans * 256 + d;
	}
	return ans;
}

int main() {
	cin >> n >> x;
	unordered_set<UINT> st;
	for (int i = 0; i < n; i++) {
		st.insert(rd());
	}
	UINT S = rd();
	UINT T = rd();
	int in_count = 0;
	for (auto v : st) {
		if (S <= v && v <= T) {
			in_count++;
		}
	}
	UINT B = T - S - in_count - 1;
	for(; S < T; S ++) {
		if(st.count(S)) {
			continue;
		}
		if(st.count(S + 1)) {
			continue;
		}
		cout << B << endl;
		return 0;
	}
	puts("-1");
	return 0;
}