#include<bits/stdc++.h>
using namespace std;

int char_to_int(char a){
	switch(a) {
		case 'B' : return 0;
		case 'G' : return 1;
		case 'R' : return 2;
		case 'Y' : return 3;
	}
}

int get_score(int col, int sum, int val){
	switch(col) {
		case 0 : return sum - val;
		case 1 : return sum + val;
		case 2 : return sum * val;
		case 3 : return val > 0 ? sum / val : 0;
	}
}

const int N = 707, inf = 1e9;
int stk[N], stack_end;
int pow_of_5[10] = {1, };

int solve() {
	int cur[N], nxt[N], n;
	char s[10];
	
	scanf("%d %s", &n, s);
	
	int origin = 0;
	for(int i = 0; i < 4; i ++) {
		origin += pow_of_5[char_to_int(s[i * 2])];
	}
	for(int i = 0; i < stack_end; i ++) {
		cur[stk[i]] = -inf;
	}
	cur[origin] = 0;
	
	for(int i = 1; i < n; i ++) {
		scanf("%s", s);
		int sum = 0, col[4], val[4];
		for(int i = 0; i < 4; i ++){
			col[i] = char_to_int(s[i * 2 + 0]);
			val[i] = s[i * 2 + 1] - '0';
			sum += val[i];
		}
		for(int j = 0; j < stack_end; j ++) {
			nxt[stk[j]] = cur[stk[j]] - sum;
		}
		for(int j = 0; j < stack_end; j ++) {
			for(int k = 0, b = stk[j]; k < 4; k ++) {
				if(b / pow_of_5[k] % 5) {
					for(int m = 0; m < 4; m ++) {
						if(col[m] == k) {
							int status = b + pow_of_5[col[m ^ 2]] - pow_of_5[k];
							int score = get_score(col[m], sum, val[m]);
							if(nxt[status] < cur[b] + score) {
								nxt[status] = cur[b] + score;
							}
						}
					}
				}
			}
		}
		memcpy(cur, nxt, sizeof cur);
	}
	int ans = -inf;
	for(int i = 0; i < stack_end; i ++){
		int j = stk[i];
		ans = max(ans, cur[j]);
	}
	
	return ans;
}

int main(){
	
	for(int i = 1; i < 10; i ++) {
		pow_of_5[i] = pow_of_5[i - 1] * 5;
	}
	
	for(int i = 0; i < 625; i ++) {
		int sum = 0;
		for(int j = 0; j < 4; j ++) {
			sum += i / pow_of_5[j] % 5;
		}
		if(sum == 4) {
			stk[stack_end] = i;
			stack_end ++;
		}
	}
	
	int T;
	
	cin >> T;
	
	while(T --) {
		cout << solve() << endl;
	}
	
	return 0;
}