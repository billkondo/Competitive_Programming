#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define debug(args...) fprintf(stderr,args)
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define REP(i,a,b) for(int i = a; i >= b; --i)

typedef long long ll;
typedef pair<int,int>pii;

const int maxn = 55;
int n;
string s[maxn];

vector<int> ans;

bool test(int id) {
    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
	    if(i != j && i != id && j != id && s[i] + s[j] == s[id]) 
		return true;
    return false;
}

void solve() {
    for(int i = 1; i <= n; ++i)
	if(test(i))
	    ans.push_back(i);
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> s[i];
    solve();
    for(auto i: ans) cout << i << " ";
    return 0;
}
