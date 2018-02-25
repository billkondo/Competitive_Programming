#include "bits/stdc++.h"
using namespace std;

const int N = 5e2 + 10;

int n, m;
int s[N], k[N], r[N], c[N];

multiset<double> C;

int solve() {
    int ans = 0;

    for(int i = 1; i <= m; ++i)
	for(int j = 1; j <= c[i]; ++j)
	    C.insert(r[i] + r[i]);

    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= k[i]; ++j) {
	    multiset<double> :: iterator it = C.upper_bound(sqrt(2) * s[i]);
	    if(it == C.end()) continue;
	    ++ans;
	    C.erase(it);
	}
	    
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &s[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &k[i]);
    for(int i = 1; i <= m; ++i) scanf("%d", &r[i]);
    for(int i = 1; i <= m; ++i) scanf("%d", &c[i]);
    printf("%d\n", solve());
    return 0;
}
