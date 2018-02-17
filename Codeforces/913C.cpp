#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int maxn = 32;
const ll INF = 1e18;

int n, L;
ll c[maxn];

ll dp[maxn];

ll Ratio(int x, int y) {
    return (1LL << (x - 1)) / (1LL << (y - 1));
}

ll f(int i) {
    if(dp[i] == -1) {
	if(!i) return dp[i] = 0;
	
	if((1 << (i - 1)) & L) {
	    dp[i] = INF;
	    for(int j = 1; j <= i; ++j)
		dp[i] = min(dp[i], c[j] * Ratio(i, j) + f(i - 1));
	}
	else 
	    dp[i] = min(f(i - 1), c[i]);
    }
    return dp[i];
}

ll solve() {
    memset(dp, -1, sizeof(dp));
    for(int i = n - 1; i >= 1; --i) c[i] = min(c[i], c[i + 1]);
    for(int i = 2; i < maxn; ++i) c[i] = min(c[i], c[i - 1] * 2LL);
    return f(maxn - 1);
}

int main() {
    scanf("%d %d", &n, &L);
    for(int i = 1; i < maxn; ++i) c[i] = INF;
    for(int i = 1; i <= n; ++i) scanf("%lld", &c[i]);
    printf("%lld\n", solve());
    return 0;
}
