#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e2 + 10;
const int MAX = 2e4 + 10;
const int ZERO = 1e4;

int n, a[maxn];

int dp[maxn][MAX];

int f(int i, int sum) {
    if(dp[i][sum] == -1) {
	if(i > n) return dp[i][sum] = (sum == ZERO) ? (0) : (INT_MIN);
	dp[i][sum] = f(i + 1, sum);
	if(sum + a[i] < MAX) dp[i][sum] = max(dp[i][sum], 1 + f(i + 1, sum + a[i]));
	if(sum - a[i] >= 0) dp[i][sum] = max(dp[i][sum], 1 + f(i + 1, sum - a[i]));
    }
    return dp[i][sum];
}

int ans;
vector<pii> points;

void solve() {
    memset(dp, -1, sizeof(dp));
    ans = f(1, ZERO);
    vector<int> pos;
    vector<int> neg;
    int i = 1;
    int sum = ZERO;

    while(i <= n) {
	if(sum + a[i] < MAX && f(i, sum) == 1 + f(i + 1, sum + a[i])) {
	    pos.push_back(a[i]);
	    sum += a[i];
	}
	else if(sum - a[i] >= 0 && f(i, sum) == 1 + f(i + 1, sum - a[i])) {
	    neg.push_back(a[i]);
	    sum -= a[i];
	}
	++i;
    }

    int x = 0;
    int y = 0;

    for(auto len: pos) {
	points.push_back({x, y});
	x += len;
	points.push_back({x, y});
	++y;
    }
    y = (int)1e9;

    for(auto len: neg) {
        points.push_back({x, y});
	x -= len;
	points.push_back({x, y});
	--y;
    }
}

int main() {
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
	scanf("%d", &a[i]);
    solve();
    printf("%d\n", ans);
    for(auto p: points) printf("%d %d\n", p.first, p.second);
    return 0;
}
