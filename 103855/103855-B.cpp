#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 4e5 + 5;

int n;
int nxt[N];
int tmp[N];
int root[N];
vector<pii> ans;
int stk[N], stk_end;
vector<int> lumps[N];

int find(int u) {
	return root[u] == u ? u: root[u] = find(root[u]);
}


void dfs(int l, int r) {
	if(l > r) return;
	const vector<int> &vec = lumps[root[l]];
	for(int i = 1; i < vec.size(); i ++) {
		ans.push_back({vec[0], vec[i]});
	}
	for(int i = 2; i < vec.size(); i ++) {
		ans.push_back({vec[i - 1], vec[i]});
	}
	
	for(int i = 0; i < vec.size(); i ++) {
		int nl, nr, x, y;
		x = vec[i];
		nl = vec[i] + 1;
		if(i + 1 < vec.size()) {
			y = vec[i + 1];
			nr = vec[i + 1] - 1;
		}
		else {
			y = vec[0];
			nr = r;
		}
		if(nl > nr) continue;
		dfs(nl, nr);
		ans.push_back({x, nl});
		ans.push_back({y, nr});
		ans.push_back({x, nr});
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1, a, b; i <= n; i ++) {
		scanf("%d %d", &a, &b);
		nxt[a] = b; nxt[b] = a;
	}
	n *= 2;
	iota(root + 1, root + n + 1, 1);
	for(int i = 1; i <= n; i ++) {
		if(nxt[i] > i) {
			stk[++ stk_end] = i;
			continue;
		}
		while(stk[stk_end] > nxt[i]) {
			tmp[stk[stk_end]] = i;
			stk_end --;
		}
		int v = nxt[i];
		while(true) {
			v = find(v);
			if(!tmp[v]) break;
			root[v] = tmp[v];
		}
		root[i] = v;
	}
	int sum = n;
	for(int i = 1; i <= n; i ++) {
		find(i);
		if(root[i] == i) sum --;
		lumps[root[i]].push_back(i);
	}
	dfs(1, n);
	printf("%d\n", sum);
	for(auto t: ans) {
		int u = t.first, v = t.second;
		if(u > v) swap(u, v);
		if(u + 1 == v || (u == 1 && v == n)) continue;
		printf("%d %d\n", u, v);
	}
	return 0;
}