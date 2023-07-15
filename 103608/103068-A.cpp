#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL gcd(LL a, LL b) {
    return ((b == 0) ? (a) : gcd(b, a % b));
}

LL calc_small_range(LL a, LL b, LL f) {
	LL ans = 0;
	while(f >= 0) {
		ans += f / b + 1;
		f -= a;
	}
	return ans;
}

LL calc_large_range(LL a, LL b, LL f) {
	LL x = f % a, z = 0, c = f / a + 1, d = a / b, f0 = f;
	LL ans = d * c * (c + 1) / 2;
	bool g = 0;
	while(f >= 0) {
		z ++;
		if(f % a == x && f != f0) g = 1;
		if(f % a < b) {
			if(z > d) {
				ans += (c + c % (b / gcd(a, b))) * (c / (b / gcd(a, b)) + 1) / 2;
			}
			else if(z < d) {
				ans -= (d - z) * c;
			}
			z = 0;
			c --;
			if(g) break;
		}
		if(g && f % a + b >= a) {
			break;
		}
		f -= b;
	}
	return ans;
}

LL solve() {
	LL a, b, f;
	cin >> a >> b >> f;
	tie(a, b) = make_pair(max(a, b), min(a, b));
	if(a < 3e4) {
		return calc_large_range(a, b, f);
	}
	return calc_small_range(a, b, f);
}

int main() {
	int T; cin >> T;
	while(T --) {
		cout << solve() << endl;
	}
	return 0;
}