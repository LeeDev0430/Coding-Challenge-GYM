#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
using DO = double;
using LL = long long;
using pii = pair < int, int > ;

const int dx[] = {
	-1,
	0,
	1,
	0,
	-1,
	1,
	1,
	-1
};
const int dy[] = {
	0,
	1,
	0,
	-1,
	1,
	1,
	-1,
	-1
};

const int N = 1e3 + 3,
	M = N * N;

const DO Ratio[] = {
	0.08,
	0.16
};

int n, m, ans[3];
LL totalX, totalY;
int height, qSize;
bool flag[N][N];
char s[N][N];
pii q[M];

bool isIn(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m && s[x][y] == '#';
}

int bfs(int x, int y) {
	totalX = 0, totalY = 0;
	height = 0, qSize = 0;
	q[qSize++] = pii(x, y);
	flag[x][y] = true;
	totalX += x, totalY += y;
	while (height < qSize) {
		x = q[height].x;
		y = q[height++].y;
		for (int i = 0; i < 8; i++) {
			int newX = x + dx[i], newY = y + dy[i];
			if (isIn(newX, newY) && !flag[newX][newY]) {
				q[qSize++] = pii(newX, newY);
				flag[newX][newY] = true;
				totalX += newX, totalY += newY;
			}
		}
	}
	DO meanX = totalX / (DO) qSize;
	DO meanY = totalY / (DO) qSize;
	DO mean = 1e18, mx = -1e18;
	for (int i = 0; i < qSize; i++) {
		DO d = hypot(meanX - q[i].x, meanY - q[i].y);
		mean = min(mean, d);
		mx = max(mx, d);
	}
	DO r = mean / mx;
	if (r > Ratio[1]) {
		return 1;
	}
	if(r > Ratio[0]) {
		return 2;
	}
	return 0;
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("votes.in", "r", stdin);
	#else
	freopen("inputdata.txt", "r", stdin);
	#endif
	int T;
	scanf("%d", & T);
	while (T--) {
		scanf("%d%d", & n, & m);
		for (int i = 0; i < n; i++) {
			scanf(" %s", s[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				flag[i][j] = false;
			}
		}
		for (int i = 0; i < 3; i++) {
			ans[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!flag[i][j] && s[i][j] == '#') {
					ans[bfs(i, j)]++;
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			printf("%d%c", ans[i], " \n" [i == 2]);
		}
	}
	return 0;
}