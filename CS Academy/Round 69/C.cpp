#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<int, ll> pii;

const int maxn = 2500 + 10;
const ll mod = 1e9 + 7;

int n;
string s;

pii dp[maxn][maxn];
bool mrk[maxn][maxn];

void upd(pii &a, pii b, int add) {
    b.first += add;
    if(b.first < a.first) {
	a.first = b.first;
	a.second = b.second;
    }
    else
	if(a.first == b.first) a.second = (a.second + b.second) % mod;
}

pii f(int i, int sum) {
    if(!mrk[i][sum]) {
	mrk[i][sum] = true;
	if(i == n) {
	    if(sum) return dp[i][sum] = {maxn, 0};
	    return dp[i][sum] = {0, 1LL};
	}

	dp[i][sum] = {maxn, 0};
	pii cmp;
	
	if(s[i] == '(') {
	    upd(dp[i][sum], f(i + 1, sum + 1), 0);
	    if(sum) upd(dp[i][sum], f(i + 1, sum - 1), 1);
	}
	else {
	    if(sum) upd(dp[i][sum], f(i + 1, sum - 1), 0);
	    upd(dp[i][sum], f(i + 1, sum + 1), 1);
	}
    }
    return dp[i][sum];
}

int main() {
    cin.sync_with_stdio(false);
    cin >> s;
    n = s.size();
    pii ans = f(0, 0);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
