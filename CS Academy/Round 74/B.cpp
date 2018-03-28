#include "bits/stdc++.h"
using namespace std;

#define debug(args...) //fprintf(stderr, args)

typedef long long ll;
const int maxn = 3e2 + 10;

int n;
int a[maxn][maxn];

ll solve() {
    ll ans = 0;
    for(int k = 1; k <= n; ++k) {
	ll total = 0;
	for(int i = 1; i <= n; ++i)
	    for(int j = 1; j <= n; ++j)
		if(i < j) {
		    if(i <= k && k < j) {
			total += a[i][j];
			debug("(%d %d)\n", i, j);
		    }
		}
		else if(i > j) {
		    if(i <= k || k < j) {
			total += a[i][j];
			debug("(%d %d)\n", i, j);
		    }
		}
	ans = max(ans, total);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
	    scanf("%d", &a[i][j]);
    printf("%lld\n", solve());
    return 0;
}
