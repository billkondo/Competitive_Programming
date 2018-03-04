#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int MAXN = 4010;
const int SQRT = 110;
const int INF = (int)1e9;

int n;

int dp[MAXN][SQRT][SQRT];
int pre[MAXN];

int f(int L, int D, int K) {
    if(dp[L][D][K] == -INF) {
	int R = n - L - D + 1;
	
	if(R - L + 1 < K) return dp[L][D][K] = 0;
	
	int sz[] = {K, K + 1};

	for(int i = 0; i < 2; ++i) 
	    if(L + sz[i] - 1 <= R) {
		int sum = pre[L + sz[i] - 1] - pre[L - 1];
		int len = R - (L + sz[i] - 1);

		if(len < sz[i]) dp[L][D][K] = max(dp[L][D][K], sum);
		else if(len < sz[i] + 1) dp[L][D][K] = max(dp[L][D][K], sum - pre[R] + pre[R - sz[i]] + f(L + sz[i], D, K + i));
		else {
		    int x = -pre[R] + pre[R - sz[i]] + f(L + sz[i], D, K + i);
		    int y = -pre[R] + pre[R - (sz[i] + 1)] + f(L + sz[i], D + 1, K + i + 1);
		    dp[L][D][K] = max(dp[L][D][K], min(sum + x, sum + y));
		}
	    }
    }
    return dp[L][D][K];
}

int solve() {
    for(int i = 1; i < MAXN; ++i)
	for(int j = 0; j < SQRT; ++j)
	    for(int k = 0; k < SQRT; ++k)
		dp[i][j][k] = -INF;
    
    return f(1, 0, 1);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
	int a;
	scanf("%d", &a);
	pre[i] = pre[i - 1] + a;
    }
    printf("%d\n", solve());	
    return 0;
}
