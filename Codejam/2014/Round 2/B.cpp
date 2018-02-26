#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 1e3 + 10;

int t;
int n;
int a[maxn];

ll solve() {
    int ans = 0;

    int L = 1;
    int R = n;

    for(int i = 1; i <= n; ++i) {
	int Min = a[L];
	int pos = L;
	
	for(int j = L + 1; j <= R; ++j) 
	    if(a[j] < Min) {
		Min = a[j];
		pos = j;
	    }
	
	if(pos -  L < R - pos) {
	    ans += pos - L;
	    for(int j = pos - 1; j >= L; --j) swap(a[j], a[j + 1]); 
	    ++L;
	}
	else {
	    ans += R - pos;
	    for(int j = pos + 1; j <= R; ++j) swap(a[j], a[j - 1]);
	    --R;
	}
    }
    
    return ans;
}

int main() {
    freopen("B.out", "w", stdout);
    scanf("%d", &t);
    int test = 0;
    while(t--) {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	printf("Case #%d: %lld\n", ++test, solve());
    }
    return 0;
}
