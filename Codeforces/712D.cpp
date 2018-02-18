#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;

const ll mod = 1e9 + 7;
const int K = 1e3 + 10;
const int T = 1e2 + 10;

int a, b, k, t;

ll dp[2][6 * K * T + 300];

int maxDif;

ll pre[6 * K * T  + 300];

void precompute(int row) {
    int id = row % 2;
    pre[0] = dp[id][0];
    for(int i = 1; i <= maxDif + maxDif; ++i)
	pre[i] = (pre[i - 1] + dp[id][i]) % mod;
}

inline ll get(int l, int r) {
    ll ans = pre[r];
    if(l) ans -= pre[l - 1];
    return ans;
}

ll solve() {
    ll ans = 0;
    maxDif = 3 * k * t + 300;

    dp[0][a - b + maxDif] = 1LL;
    for(int i = 1; i <= t; ++i) {
	int l = 0;
	int r = -1;

	precompute(i - 1);
	ll sum = 0;
	int id = i % 2;
	
	for(int j = 0; j <= maxDif + maxDif; ++j) {
	    
	    while(r + 1 <= maxDif + maxDif && r + 1 <= j + (k + k)) {
		++r;
		sum = (sum + get(j, r)) % mod;
	    }

	    sum = (sum - get(l, j - 1) + mod) % mod;
	    while(l < j - (k + k)) ++l;	    

	    dp[id][j] = sum;
	}
    }

    int id = t % 2;
    for(int diff = maxDif + 1; diff <= maxDif + maxDif; ++diff)
	ans = (ans + dp[id][diff]) % mod;

    return ans;
}

int main() {
    scanf("%d %d %d %d", &a, &b, &k, &t);
    printf("%lld\n", solve());
    return 0;
}
