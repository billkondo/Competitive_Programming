#include "bits/stdc++.h"
using namespace std;

int t;
int n, x;

int main() {
    freopen("A.out", "w", stdout);
    scanf("%d", &t);
    int test = 0;
    while(t--) {
	scanf("%d %d", &n, &x);
	multiset<int> S;
	for(int i = 1; i <= n; ++i) {
	    int sz;
	    scanf("%d", &sz);
	    S.insert(sz);
	}
	int ans = 0;
	while(!S.empty()) {
	    ++ans;
	    int sz = *S.begin();
	    S.erase(S.begin());
	    multiset<int> :: iterator it = S.upper_bound(x - sz);
	    if(it != S.begin()) {
		--it;
		S.erase(it);
	    }
	}
	printf("Case #%d: %d\n", ++test, ans);
    }
}
