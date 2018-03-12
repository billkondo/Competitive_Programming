#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e2 + 10;

int t;
int n, u, d;

int h[maxn];

int dp[maxn][2];

int f(int i, int flag) {
    if(dp[i][flag] == -1) {
	dp[i][flag] = i;

	if(i + 1 <= n) {
	    if(h[i + 1] >= h[i] && h[i + 1] - h[i] <= u)
		dp[i][flag] = f(i + 1, flag);
	    else
		if(h[i + 1] < h[i]) {
		    if(h[i] - h[i + 1] <= d) dp[i][flag] = f(i + 1, flag);
		    else if(!flag) dp[i][flag] = f(i + 1, 1);
		}
	}
    }
    return dp[i][flag];
}

int main() {
    cin.sync_with_stdio(false);
    cin >> t;
    while(t--) {
	cin >> n >> u >> d;
	for(int i = 1; i <= n; ++i) cin >> h[i];
	memset(dp, -1, sizeof(dp));
	cout << f(1, 0) << endl;
    }
    return 0;
}
