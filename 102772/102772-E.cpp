#include <bits/stdc++.h>

using namespace std;

vector<string> grid;

int main()  {
	int n, m; cin >> n >> m;
	
	grid.resize(n + 1);
	for(auto & x : grid) {
		x.resize(m + 1);
	}
	
	for(int i = 1; i < m; i++) {
		grid[1][i] = 'R';
	}
	
	grid[1][m] = 'D';
	
	for(int j = m; j >= (m % 2 == 0 ? 1 : 3); j--) {
		if((j & 1) == (m & 1)) {
			for(int i = 2; i < n; i++) {
				grid[i][j] = 'D';
			}
			grid[n][j] = 'L';
		}
		else {
			for(int i = 3; i <= n; i++) {
				grid[i][j] = 'U';
			}
			grid[2][j] = 'L';
		}
	}
	
	if(m & 1) {
		for(int i = n; i >= 2; i--) {
			if(i % 2 == n % 2) {
				grid[i][1] = 'U';
				grid[i][2] = 'L';
			} else {
				grid[i][1] = 'R';
				grid[i][2] = 'U';
			}
		}
	}
	else {
		grid[2][1] = 'U';
	}
	
	int snake_x, snake_y, apple_x, apple_y, eaten = 0;
	string s;
	
	cin >> snake_x >> snake_y >> apple_x >> apple_y;
	
	
	for(char current_direction; ; ) {
		current_direction = grid[snake_x][snake_y];
		if(snake_x == 2 && snake_y == 1) {
			if(apple_x == 1 && apple_y == 1) {
				current_direction = 'U';
			}
		}
		cout << current_direction << endl;
		cin >> s;
		if(s == "fail" || s == "win") {
			exit(0);
		} else if(s == "new") {
			cin >> apple_x >> apple_y;
		}
		if(current_direction == 'L') {
			snake_y -= 1;
		} else if(current_direction == 'R') {
			snake_y += 1;
		} else if(current_direction == 'U') {
			snake_x -= 1;
		} else {
			snake_x += 1;
		}
	}
	return 0;
}