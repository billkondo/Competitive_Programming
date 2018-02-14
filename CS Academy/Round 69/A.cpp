#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e2 + 10;

int n, a[maxn];

int ans[maxn];

void solve() {
    int last = 1;
    for(int i = 2; i <= n; ++i) 
	if(a[last] > a[i]) 
	    ++ans[last];
	else {
	    last = i;
	    ++ans[last];
	}
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
	scanf("%d", &a[i]);
    solve();
    for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
    return 0;
}
