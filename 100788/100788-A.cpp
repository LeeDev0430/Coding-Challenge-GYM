#include <bits/stdc++.h>

using namespace std;
using DO = double;

const int N = 1e5 + 10;
DO a[N];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("anagrams.in", "r", stdin);
	freopen("anagrams.out", "w", stdout);
	#endif
	int n;
	scanf("%d", & n);
	DO sum = 0;
	for (int i = 0; i < n; ++i) {
		int d;
		scanf("%d", & d);
		sum += sqrt(d);
	}
	int m;
	scanf("%d", & m);
	DO seg = 0;
	for (int i = 1; i <= m; ++i) {
		int d;
		scanf("%d", & d);
		a[i] = sqrt(d);
		seg += a[i];
		if (i > n) {
			seg -= a[i - n];
		}
		if (fabs(seg - sum) < 1e-6) {
			puts("YES");
			printf("%d\n", i - n + 1);
			return 0;
		}
	}
	puts("NO");
	return 0;
}