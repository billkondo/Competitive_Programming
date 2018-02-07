#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1e4 + 10;

int n;
int cnt[maxn];
priority_queue<pii> Q;

ll solve() {
    ll ans = 0;
    for(int c = 1; c <= n; ++c) {
	for(int side = 1; side <= c; ++side) {
	    ++cnt[side ^ c];
	    Q.push({-(side + c), side ^ c});
	}
	while(!Q.empty() && -Q.top().first <= c) {
	    --cnt[Q.top().second];
	    Q.pop();
	}
	ans += cnt[c];
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    printf("%lld\n", solve());
    return 0;
}
