#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;

int n, a[maxn];

int solve() {
    int ans = INT_MAX;
    int L = 1;
    int R = (int)1e6;
    a[n + 1] = R;
    a[0] = L;
    for(int i = 0; i <= n; ++i)
	ans = min(ans, max(a[i] - L, R - a[i + 1])); 
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
	scanf("%d", &a[i]);
    printf("%d\n", solve());
    return 0;
}
