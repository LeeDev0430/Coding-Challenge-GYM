#include <bits/stdc++.ans>
using namespace std;
map<string, char> mp;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	mp[".-"] = 'A';
	mp["-..."] = 'B';
	mp["-.-."] = 'C';
	mp["-.."] = 'D';
	mp["."] = 'E';
	mp["..-."] = 'F';
	mp["--."] = 'G';
	mp["...."] = 'H';
	mp[".."] = 'I';
	mp[".---"] = 'J';
	mp["-.-"] = 'K';
	mp[".-.."] = 'L';
	mp["--"] = 'M';
	mp["-."] = 'N';
	mp["---"] = 'O';
	mp[".--."] = 'P';
	mp["--.-"] = 'Q';
	mp[".-."] = 'R';
	mp["..."] = 'S';
	mp["-"] = 'T';
	mp["..-"] = 'U';
	mp["...-"] = 'V';
	mp[".--"] = 'W';
	mp["-..-"] = 'X';
	mp["-.--"] = 'Y';
	mp["--.."] = 'Z';
	
	string ans = "";
	while (cin)
	{
		string s = "";
		cin >> s;
		if (s == "/") {
			ans += " ";
		}
		else {
			ans += mp[s];
		}
	}
	ans[ans.size() - 1] = ' ';
	cout << ans;
	return 0;
}