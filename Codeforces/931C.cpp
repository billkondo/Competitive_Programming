#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;

int n;
int x[maxn];
int y[maxn];

int Min, Max;
int cnt[3];

int solve() {
    Min = INT_MAX;
    Max = INT_MIN;

    for(int i = 1; i <= n; ++i) {
	Min = min(Min, x[i]);
	Max = max(Max, x[i]);
    }

    if(Max - Min <= 1) {
	for(int i = 1; i <= n; ++i) y[i] = x[i];
	return n;
    }

    for(int i = 1; i <= n; ++i)
	if(Min == x[i]) ++cnt[0];
	else if(Max == x[i]) ++cnt[2];
	else ++cnt[1];

    int val[] = {Min, Min + 1, Max};

    if(n - 2 * min(cnt[0], cnt[2]) < n - 2 * (cnt[1] / 2)) {
	int ans = n - 2 * min(cnt[0], cnt[2]);
	int k = min(cnt[0], cnt[2]);

	while(k) {
	    --cnt[0];
	    --cnt[2];
	    cnt[1] += 2;
	    --k;
	}
	
	for(int i = 1; i <= n; ++i)
	    for(int j = 0; j <= 2; ++j)
		if(cnt[j]) {
		    --cnt[j];
		    y[i] = val[j];
		    break;
		}
	
	return ans;
    }
    else {
	int ans = n - 2 * (cnt[1] / 2);
	int k = cnt[1] / 2;

	while(k) {
	    ++cnt[0];
	    ++cnt[2];
	    cnt[1] -= 2;
	    --k;
	}
	
	for(int i = 1; i <= n; ++i)
	    for(int j = 0; j <= 2; ++j)
		if(cnt[j]) {
		    --cnt[j];
		    y[i] = val[j];
		    break;
		}

	return ans;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &x[i]);
    printf("%d\n", solve());
    for(int i = 1; i <= n; ++i) printf("%d ", y[i]);
    printf("\n");
    return 0;
}
