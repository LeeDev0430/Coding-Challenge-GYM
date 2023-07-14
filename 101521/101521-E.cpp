#include <bits/stdc++.h>

using namespace std;
const int NN = 1010;

int degree[NN], sz[NN];
vector<int> adj[1010], tmp;

int dfs (int u, int fa = -1) {
	sz[u] = 1;
	for (auto v : adj[u]) {
		if (v != fa) {
			sz[u] += dfs (v, u);
		}
	}
	return sz[u];
}

int main () {
	int tcase, n;
	cin >> tcase >> n;
	while(tcase --) {
		int cnt = 0;
		for (int i = 0; i < n; i ++) {
			degree[i] = 0;
			adj[i].clear ();
		}
		for (int i = 1, s; i < n; i ++) {
			scanf ("%d", & s);
			adj[i].push_back (s);
			adj[s].push_back (i);
			degree[i] ++;
			degree[s] ++;
		}
		for (int i = 0; i < n; i ++) {
			if (degree[i] >= 9) {
				dfs (i);
				tmp.clear ();
				for (auto v : adj[i]) {
					tmp.push_back (sz[v]);
				}
				sort (tmp.begin (), tmp.end ());
				int sum = 0;
				for(int j = 6; j < 9; j ++) {
					sum += tmp[tmp.size() - j];
				}
				if(cnt < sum) {
					cnt = sum;
				}
			}
		}
		puts(cnt < 67 ? "R" : "L");
	}
	return 0;
}