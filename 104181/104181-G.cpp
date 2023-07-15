#include<bits/stdc++.h>
using namespace std;
using DO = double;

const int N = 200005;
const DO pi = acosl(-1.0);

int calc() {
	DO r, k;
	scanf("%lf %lf", &r, &k);
	if (k <= pi) {
		return 0;
	}
	DO s = (r * (k - pi)) / k;
	if(s > (r / k))
		return 1e9;
	return ceil(s);
}

int need[N];

int solve() {
	int n, energy;
	scanf("%d %d", &n, &energy);
	for(int i = 0; i < n; i ++) {
		need[i] = calc();
	}
	sort(need, need + n);
	int ans = 0;
	for(int i = 0; i < n; i ++) {
		if(energy >= need[i]) {
			energy -= need[i];
			ans ++;
		}
	}
	return ans;
}

int main() {
	cout << solve() << endl;
	return 0;
}