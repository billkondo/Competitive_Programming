#include "bits/stdc++.h"
using namespace std;

int n;
string s;

vector<char> stk;
char c[] = {'a', 'e', 'i', 'o', 'u', 'y'};

void solve() {
    map<char, int> m;
    for(int i = 0; i < 6; ++i)
	m[c[i]] = 1;

    for(int i = 0; i < n; ++i) {
	if(m[s[i]] && !stk.empty() && m[stk.back()]) continue;
	stk.push_back(s[i]);
    }
}

int main() {
    cin.sync_with_stdio(false);
    cin >> n >> s;
    solve();
    for(auto i: stk) cout << i;
    return 0;
}
