#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

ll n;
int k;

inline int get(int x) {
    ll cur = x;
    int days = 1;
    while(n - cur > k - x) {
	++days;
	cur = cur + min(cur, (n - cur) / 2);
    }
    return days;
}

int solve() {
    int ans = INT_MAX;
    if(k >= n) return ans = 1;
    for(int x = 1; x <= k - 1; ++x)
	ans = min(ans, get(x));
    return ans;
}

int main() {
    scanf("%lld %d", &n, &k);
    printf("%d\n", solve());
    return 0;
}
