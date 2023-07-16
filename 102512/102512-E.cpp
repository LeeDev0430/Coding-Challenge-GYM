#include <bits/stdc++.h>

using namespace std;

constexpr int Com(int n) {
	return n * (n - 1) / 2;
}

const int N = 200,
	MAX = Com(200);
bitset < MAX + 10 > bit[N + 1];

void solve() {
	int x;
	scanf("%d", & x);
	vector < vector < int >> ans;
	if (x <= N) {
		ans.assign(1, vector < int > (x, 7));
	} else {
		int z = 1;
		while (z * Com(N) + N * Com(z + 1) < x + 4949) {
			z += 1;
		}
		ans.assign(z, vector < int > (N));
		x -= N * Com(z + 1);

		for (int i = 0; i < z; i++) {
			int f = min(MAX, x);
			while (!bit[N][f]) {
				f -= 1;
			}
			x -= f; {
				int g = N;
				int val = i * N + 1;
				int cur = 0;
				while (g > 0) {
					int t = 1;
					while (!bit[g - t][f - Com(t)]) {
						t += 1;
					}
					g -= t;
					f -= Com(t);
					for (int j = 0; j < t; j++) {
						ans[i][cur] = val;
						cur++;
						val++;
					}
					val--;
				}
			}
		}
	}
	int h = int(ans.size());
	int w = ans[0].size();
	printf("%d %d\n", h, w);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("%d%c", ans[i][j], j + 1 == w ? '\n' : ' ');
		}
	}
}

int main() {
	bit[0][0] = true;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= x; y++) {
			bit[x] |= bit[x - y] << Com(y);
		}
	}
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}