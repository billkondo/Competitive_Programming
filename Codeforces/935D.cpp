#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;
const ll mod = 1e9 + 7;

int n;
ll m;

ll a[maxn], b[maxn];

ll dp[2][maxn];

ll f(int flag, int i) {
    if(dp[flag][i] == -1) {
	if(i > n) return dp[flag][i] = flag;
	dp[flag][i] = 0LL;
	if(!flag) {
	    if(!a[i]) {
		if(b[i]) 
		    dp[flag][i] = ((m - b[i]) * f(1, i + 1) + f(0, i + 1)) % mod;
		else {
		    ll x = m * (m - 1) / 2;
		    x %= mod;
		    dp[flag][i] = (m * f(0, i + 1) + x * f(1, i + 1)) % mod;
		}		    
	    }
	    else {
		if(b[i]) {
		    if(a[i] > b[i]) dp[flag][i] = f(1, i + 1);
		    else if(a[i] == b[i]) dp[flag][i] = f(0, i + 1);
		}
		else 
		    dp[flag][i] = ((a[i] - 1) * f(1, i + 1) + f(0, i + 1)) % mod;
	    }
	}
	else {
	    ll mult = 1LL;

	    if(!a[i]) mult = (mult * m) % mod;
	    if(!b[i]) mult = (mult * m) % mod;

	    dp[flag][i] = (mult * f(1, i + 1)) % mod;
	}
    }
    return dp[flag][i];
}

ll fpow(ll a, ll b) {
    if(!b) return 1;
    if(b % 2) return (a * fpow(a, b - 1)) % mod;
    ll x = fpow(a, b / 2);
    return (x * x) % mod;
}

ll solve() {
    memset(dp, -1, sizeof(dp));
    ll up = f(0, 1);
    ll down = 1LL;
    for(int i = 1; i <= n; ++i) {
	if(!a[i]) down = (down * m) % mod;
	if(!b[i]) down = (down * m) % mod;
    }
    
    down = fpow(down, mod - 2);
    return (up * down) % mod;
}

int main() {
    scanf("%d %lld", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
    printf("%lld\n", solve());
    return 0;
}
