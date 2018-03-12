#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;
const int BIT = 31;

int n, q;
int a[maxn];

int bit[BIT][maxn];

void solve() {
    for(int i = 1; i <= n; ++i) {
	for(int k = 0; k < BIT; ++k) {
	    bit[k][i] = bit[k][i - 1];
	    if((1 << k) & a[i]) ++bit[k][i];
	}
    }
}

int query(int l, int r) {
    int len = r - l + 1;
    int x = 0;

    for(int k = 0; k < BIT; ++k) {
	int cnt = bit[k][r] - bit[k][l - 1];
	if(len - cnt > cnt) x += (1 << k);
    }

    return x;
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    solve();
    while(q--) {
	int l, r;
	scanf("%d %d", &l, &r);
	printf("%d\n", query(l, r));
    }
    return 0;
}
