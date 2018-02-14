#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;

int n, a[maxn];

int pre[maxn];
int suf[maxn];

ll cnt;
int x, y;

bool eq = true;

bool solve() {
    if(n == 1) {
	cnt = 1;
	x = y = 1;
	return true;
    }

    a[n + 1] = INT_MAX;
    pre[1] = true;
    for(int i = 2; i <= n; ++i)
	pre[i] = (a[i] >= a[i - 1]) & pre[i - 1];

    for(int i = 2; i <= n; ++i) eq = eq & (a[i] == a[1]);

    if(pre[n]) {
	x = y = 1;
	
	if(eq) cnt = 1LL * n  * (n + 1) / 2LL;
	else cnt = n;

	return true;
    }
    
    suf[n] = true;
    for(int i = n - 1; i >= 1; --i)
	suf[i] = (a[i] <= a[i + 1]) & suf[i + 1];

    int L = 0;
    int R = n + 1;

    while(pre[L + 1]) ++L;
    while(suf[R - 1]) --R;

    cnt = 1;

    while(L - 1 >= 1 && a[L - 1] == a[L]) --L;
    while(R + 1 <= n && a[R + 1] == a[R]) ++R;

    bool flag = true;

    for(int i = L; i < R; ++i)
	flag = flag & (a[i] >= a[i + 1]);

    x = L;
    y = R;

    flag = flag & (a[L] <= a[R + 1]);
    flag = flag & (a[L - 1] <= a[R]);
    
    return flag;
}

int main() {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
	scanf("%d", &a[i]);

    if(solve()) {
	printf("%lld\n", cnt);
	printf("%d %d\n", x, y);
    }
    else printf("0\n");
}
