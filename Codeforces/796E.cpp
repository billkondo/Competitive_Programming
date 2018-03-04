#include "bits/stdc++.h"
using namespace std;

const int N = 1e3 + 10;
const int K = 50 + 10;
const int INF = 0x3f3f3f3f;

int n, p, k;

int r, s;
int a[N], b[N];

int A[N], B[N];

int dp[2][2 * N][K][K];

int solve() {
    p = min(p, 2 * ((n / k) + (n % k != 0)));
    memset(dp, -INF, sizeof(dp));

    dp[1][p][0][0] = 0;

    for(int row = 1; row <= n; ++row) {
	int i = row & 1;

	for(int j = 0; j <= p; ++j)
	    for(int a = 0; a < k; ++a)
		for(int b = 0; b < k; ++b)
		    dp[i ^ 1][j][a][b] = -INF;

	for(int j = 0; j <= p; ++j)
	    for(int a = 0; a < k; ++a)
		for(int b = 0; b < k; ++b) 
		    if(dp[i][j][a][b] != -INF) {
			int cost = 0;
			if((A[row] && a) || (B[row] && b)) ++cost;
			dp[i ^ 1][j][max(0, a - 1)][max(0, b - 1)] = max(dp[i ^ 1][j][max(0, a - 1)][max(0, b - 1)], dp[i][j][a][b] + cost);

			if(j) {
			    dp[i ^ 1][j - 1][k - 1][max(0, b - 1)] = max(dp[i ^ 1][j - 1][k - 1][max(0, b - 1)], dp[i][j][a][b] + max(A[row], cost));
			    dp[i ^ 1][j - 1][max(0, a - 1)][k - 1] = max(dp[i ^ 1][j - 1][max(0, a - 1)][k - 1], dp[i][j][a][b] + max(B[row], cost));
			}
		    }
		
    }

    int ans = 0;
    int i = (n + 1) & 1;

    for(int j = 0; j <= p; ++j)
	for(int a = 0; a < k; ++a)
	    for(int b = 0; b < k; ++b)
		ans = max(ans, dp[i][j][a][b]);
    
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &p, &k);
    
    scanf("%d", &r);
    for(int i = 1; i <= r; ++i) {
	scanf("%d", &a[i]);
	A[a[i]] = 1;
    }

    scanf("%d", &s);
    for(int i = 1; i <= s; ++i) {
	scanf("%d", &b[i]);
	B[b[i]] = 1;
    }
    
    printf("%d\n", solve());
    return 0;
}
