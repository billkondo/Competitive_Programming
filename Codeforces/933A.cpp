#include "bits/stdc++.h"
using namespace std;

const int maxn = 2e3 + 10;

int n;
int a[maxn];

int pre[maxn][maxn];
int suf[maxn][maxn];

int dp[maxn];

int bit[maxn];

void add(int idx, int val) {
    while(idx <= n) {
	bit[idx] = max(bit[idx], val);
	idx += (idx & -idx);
    }
}

int query(int idx) {
    int ret = 0;
    while(idx) {
	ret = max(ret, bit[idx]);
	idx -= (idx & -idx);
    }
    return ret;
}

int solve() {
    for(int i = 1; i <= n; ++i) {
	dp[i] = 1;
	for(int j = 1; j < i; ++j)
	    if(a[j] <= a[i])
		dp[i] = max(dp[i], dp[j] + 1);
	
	for(int j = 1; j <= n; ++j) pre[i][j] = pre[i][j - 1];
	for(int j = a[i]; j <= n; ++j) pre[i][j] = max(pre[i][j], dp[i]);
    }

    memset(dp, 0, sizeof(dp));
    for(int i = n; i >= 1; --i) {
	dp[i] = 1;
	for(int j = i + 1; j <= n; ++j)
	    if(a[j] >= a[i])
		dp[i] = max(dp[i], dp[j] + 1);

	for(int j = 1; j <= n; ++j) suf[i][j] = suf[i][j + 1];
	for(int j = a[i]; j >= 1; --j) suf[i][j] = max(suf[i][j], dp[i]);
    }

    int ans = 0;
    for(int i = 1; i <= n; ++i) {
	ans = max(ans, dp[i]);
	memset(bit, 0, sizeof(bit));
	add(a[i], 1);
	for(int j = i - 1; j >= 1; --j) {
	    if(a[j] < a[i]) continue;
	    int q = query(a[j]);
	    add(a[j], q + 1);
	    ans = max(ans, q + 1 + pre[j - 1][a[i]] + suf[i + 1][a[j]]);
	}    
    }
		
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
	scanf("%d", &a[i]);
    printf("%d\n", solve());
    return 0;
}
