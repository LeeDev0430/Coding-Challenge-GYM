#include<bits/stdc++.h>

using namespace std;


int cant;
map<long long , long long> root;

long long Find(long long v) {
	if (!root[v]) {
		return v;
	}
	return root[v] = Find(root[v]);
}

void Union(long long v, long long u) {
	v = Find(v);
	u = Find(u);
	if (v != u) {
		root[v] = u;
		if (Find(v) == Find(v ^ 1) || Find(u) == Find(-((-u) ^ 1))) {
			cant = 0;
		}
	}
}

int main() {
	int n;
	cin >> n;
	cant = 1;
	while (n --) {
		long long x, y, axy, bxy;
		scanf("%I64d %I64d %I64d %I64d", &x, &y, &axy, &bxy);
		if (axy == bxy) {
			Union(x * 2, - y * 2);
			Union(x * 2 + 1, -(y * 2 + 1));
		}
		else {
			Union(x * 2, -(y * 2 + 1)), Union(x * 2 + 1, - y * 2);
		}
		if (cant) {
			puts("Yes");
		}
		else {
			puts("No");
		}
	}
	return 0;
}