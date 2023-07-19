#include<bits/stdc++.h>

using namespace std;
typedef long long INT;

const int maxn = 1e5 + 10;

struct PT{
	int id;
	INT x, y;
	double angle;
	PT operator - (const PT & b) const{
		PT res;
		res.x = x - b.x;
		res.y = y - b.y;
		return res;
	}
	PT operator * (const int & b) const{
		PT res;
		res.x = x * b;
		res.y = y * b;
		return res;
	}
	INT operator * (const PT & b) const{
		return (INT) x * b.x + (INT) y * b.y;
	}
	bool operator <(const PT &b) const{
		return angle < b.angle;
	}
}p[maxn];

set<PT> res_PT;
vector<int> ans;

bool is_ok(const PT &a, const PT &b){
	return (a - b * 2) * (a - b * 2) > a * a;
}

int main(){
	freopen("nothingontv.in", "r", stdin);
	freopen("nothingontv.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i += 1){
		p[i].id = i;
		cin >> p[i].x >> p[i].y;
		p[i].angle = atan2(p[i].y, p[i].x);
	}
	sort(p + 1, p + n + 1, [](const PT &a, const PT &b) {
		return a * a < b * b;
	});
	res_PT.insert(p[1]);
	for(int i = 2; i <= n; i ++){
		bool is_good;
		auto nearest_PT = res_PT.lower_bound(p[i]);
		if(nearest_PT == res_PT.end() || nearest_PT == res_PT.begin()) {
			if(is_ok(p[i], *res_PT.begin()) && is_ok(p[i], *res_PT.rbegin())) {
				res_PT.insert(p[i]);
			}
		}
		else {
			if(is_ok(p[i], *nearest_PT) && is_ok(p[i], *(-- nearest_PT))){
				res_PT.insert(p[i]);
			}
		}
	}
	for(PT a : res_PT) {
		ans.push_back(a.id);
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(int i : ans) {
		cout << i << ' ';
	}
	return 0;
}