#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
using pii = pair < int, int > ;

const int N = 1e3 + 10;
int n;
pair < pii, pii > a[N], b[N];
map < pii, int > dif;

pii operator - (const pii & a, const pii & b) {
	return pii(a.x - b.x, a.y - b.y);
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("matches.in", "r", stdin);
	freopen("matches.out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x.x >> a[i].x.y >> a[i].y.x >> a[i].y.y;
		if (a[i].x > a[i].y) {
			swap(a[i].x, a[i].y);
		}
	}

	for (int j = 1; j <= n; j++) {
		cin >> b[j].x.x >> b[j].x.y >> b[j].y.x >> b[j].y.y;
		if (b[j].x > b[j].y) {
			swap(b[j].x, b[j].y);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i].y - a[i].x == b[j].y - b[j].x) {
				dif[a[i].x - b[j].x]++;
			}
		}
	}

	int ans = n;

	for (auto p: dif) {
		ans = min(ans, n - p.y);
	}

	cout << ans << endl;

	return 0;
}