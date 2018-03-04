#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int maxn = 1e6 + 10;
const ll mod = 1e9 + 7;

int n, h[maxn];

ll solve() {
    ll ans = 0;
    for(int i = 1; i <= n; ++i) ans = (ans + h[i] - 1) % mod;

    ll S = min(h[1], h[2]) - 1;
    h[n + 1] = INT_MAX;
    for(int i = 2; i <= n; ++i) {
	ll R = min(h[i], h[i - 1]) - 1;
	ll r = min(h[i], h[i + 1]) - 1;
	ll Min = min(h[i], min(h[i - 1], h[i + 1])) - 1;
	ans = (ans + S * R) % mod;
	S = (S * Min + r) % mod;
    }
    
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    printf("%lld\n", solve());
    return 0;
}
