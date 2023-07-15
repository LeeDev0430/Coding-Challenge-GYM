#include <bits/stdc++.h>

using namespace std;

using uINT = unsigned long long;

#define x first
#define y second

const pair<int, int> position[15] = {
	{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2},
};

struct Puzzle {
	int data[4][4];
	string ans;
	int score;
	int cx, cy;

	int get(int x, int y) const {
		int d = data[x][y];
		assert(d >= 0);
		return abs(x - position[d].x) + abs(y - position[d].y);
	}

	void init() {
		score = 0;
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j) {
				int x = data[i][j];
				if(x == -1) { cx = i, cy = j; continue; }
				else score += get(i, j);
			}
	}

	Puzzle U() const {
		Puzzle d = *this;
		assert(cx < 3);
		d.data[cx][cy] = d.data[cx + 1][cy];
		d.data[cx + 1][cy] = -1;
		d.ans += "U";
		++d.cx;
		d.score += d.get(cx, cy) - get(d.cx, d.cy);
		return d;
	}
	Puzzle D() const {
		Puzzle d = *this;
		assert(cx > 0);
		d.data[cx][cy] = d.data[cx - 1][cy];
		d.data[cx - 1][cy] = -1;
		d.ans += "D";
		--d.cx;
		d.score += d.get(cx, cy) - get(d.cx, d.cy);
		return d;
	}
	Puzzle L() const {
		Puzzle d = *this;
		assert(cy < 3);
		d.data[cx][cy] = d.data[cx][cy + 1];
		d.data[cx][cy + 1] = -1;
		d.ans += "L";
		++d.cy;
		d.score += d.get(cx, cy) - get(d.cx, d.cy);
		return d;
	}
	Puzzle R() const {
		Puzzle d = *this;
		assert(cy > 0);
		d.data[cx][cy] = d.data[cx][cy - 1];
		d.data[cx][cy - 1] = -1;
		d.ans += "R";
		--d.cy;
		d.score += d.get(cx, cy) - get(d.cx, d.cy);
		return d;
	}

	uINT hash() {
		uINT ans = 0;
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				ans = (ans << 4) | (data[i][j] & 0xF);
		return ans;
	}

	friend bool operator <(const Puzzle& a, const Puzzle& b) {
		return a.ans.length() + a.score * 5 > b.ans.length() + b.score * 5;
	}
};

Puzzle st;
bool flag[15];
string ans;

void solve() {
	for(int i = 0, x; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			scanf("%d", &x);
			st.data[i][j] = x - 1;
		}
	}
	st.init();
	int c = 3 - st.cx;
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j) {
			int x = st.data[i][j];
			if(x == -1) continue;
			else {
				flag[x] = true;
				for(int k = x + 1; k < 15; ++k)
					c += flag[k];
			}
		}
	if(c % 2 == 1) puts("No");
	else {
		puts("Yes");
		if(st.score == 0) ans = "";
		else {
			priority_queue<Puzzle> pq;
			unordered_set<uINT> flag;
			pq.push(st);
			flag.insert(st.hash());
			while(true) {
				auto data = move(pq.top());
				pq.pop();
				if(data.cx < 3) {
					auto u = data.U();
					if(u.score == 0) {
						ans = u.ans;
						break;
					}
					if(flag.emplace(u.hash()).y)
						pq.push(move(u));
				}
				if(data.cx > 0) {
					auto d = data.D();
					if(d.score == 0) {
						ans = d.ans;
						break;
					}
					if(flag.emplace(d.hash()).y)
						pq.push(move(d));
				}
				if(data.cy < 3) {
					auto l = data.L();
					if(l.score == 0) {
						ans = l.ans;
						break;
					}
					if(flag.emplace(l.hash()).y) {
						pq.push(move(l));
					}
				}
				if(data.cy > 0) {
					auto r = data.R();
					if(r.score == 0) {
						ans = r.ans;
						break;
					}
					if(flag.emplace(r.hash()).y) {
						pq.push(move(r));
					}
				}
			}
		}
		printf("%d\n", ans.length());
		puts(ans.data());
	}
}

int main() {
	solve();
	return 0;
}