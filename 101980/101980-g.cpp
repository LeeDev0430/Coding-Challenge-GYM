#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10;
int d[N];

int main() {
	int n, u, v; cin >> n;
	bool chain = true;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &u, &v);
		d[u] ++;
		d[v] ++;
		if(d[u] > 2 or d[v] > 2) {
			chain = false;
		}
	}
	if(chain or n % 2) {
		puts("Billy");
	}
	else {
		puts("Ricardo");
	}
	return 0;
}