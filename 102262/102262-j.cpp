#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 10;
char str[N];
int n;

int insert_char(int id, char c) {
	for(int i = 0; i < id; i ++) {
		putchar(str[i]);
	}
	putchar(c);
	for(int i = id; i < n; i ++) {
		putchar(str[i]);
	}
	return 0;
}

int solve() {
	stack<pair<char, int>> stk;
	stk.push(make_pair('\0', 0));
	string status = "initial";
	
	for (int i = 0, str_id = 0; i < n; i++) {
		char s = str[i];
		
		if(status == "initial") {
			if (s == '"') {
				status = "startedKey";
				str_id = i;
			}
			else if (s == '{') {
				stk.push({'{', i});
				status = "startedDictionary";
			}
			else if (s == '}') {
				return insert_char(i, '{');
			}
			else {
				return insert_char(i, '"');
			}
			continue;
		}
		
		if(status == "startedDictionary") {
			if (s == '"') {
				status = "startedString";
			}
			else if (s == '}') {
				stk.pop();
				status = "endedKey";
			}
			else if (s == ',') {
				return insert_char(i, '}');
			}
			else {
				return insert_char(i, '"');
			}
			continue;
		}
		
		if(status == "startedString") {
			if (s == '"') {
				status = "endedString";
			}
			else if (s == ',' || s == ':' || s == '{' || s == '}') {
				return insert_char(i, '"');
			}
			continue;
		}
		
		if(status == "endedString") {
			if (s == ':') {
				status = "initial";
			}
			else {
				return insert_char(i, ':');
			}
			continue;
		}
		
		if(status == "startedKey") {
			if (s == '"') {
				status = "endedKey";
			}
			else if (s == ',' || s == ':' || s == '{' || s == '}') {
				return insert_char(i, '"');
			}
			continue;
		}
		
		if(status == "endedKey") {
			if (s == ':') {
				return insert_char(str_id, '{');
			}
			else if (s == ',') {
				status = "startedDictionary";
			}
			else if (s == '"' || s == '{') {
				return insert_char(i, ',');
			}
			else if (s == '}') {
				stk.pop();
			}
			continue;
		}
	}
	
	auto rem = stk.top(); stk.pop();
	if (rem.first != '\0') 
		return insert_char(n, '}');
	return insert_char(n, '"');
}

int main() {
	scanf("%s", str);
	n = strlen(str);
	solve();
	return 0;
}