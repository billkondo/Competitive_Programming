#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

const int maxn = 2e3 + 10;
const int INF = 1e9;

int n, h;
double p;

int x[maxn];

bool ok[maxn][maxn][2][2];
double dp[maxn][maxn][2][2];

int L[maxn];
int R[maxn];

double f(int l, int r, int right, int left) {
    if(!ok[l][r][right][left]) {
	ok[l][r][right][left] = true;
	
	if(l > r) return dp[l][r][right][left] = 0.0;

	double toLeft = p / 2.0;
	double toRight = (1.0 - p) / 2.0;

	if(l == r) {
	    toLeft *= 2.0;
	    toRight *= 2.0;

	    // Fall to Left
	    if(right) dp[l][r][right][left] += toLeft * min(max(0, x[l] - x[l - 1] - h), h);
	    else dp[l][r][right][left] += toLeft * min(x[l] - x[l - 1], h);

	    // Fall to Right
	    if(left) dp[l][r][right][left] += toRight * min(max(0, x[r + 1] - h - x[r]), h);
	    else dp[l][r][right][left] += toRight * min(x[r + 1] - x[r], h);
	}
	else {
	    // Fall to Left (Left Tree)
	    if(right) dp[l][r][right][left] += toLeft * (min(max(0, x[l] - x[l - 1] - h), h) + f(l + 1, r, 0, left));
	    else dp[l][r][right][left] += toLeft * (min(x[l] - x[l - 1], h) + f(l + 1, r, 0, left));

	    // Fall to Right (Left Tree)
	    int leftPoint = x[L[l]] + h;
	    if(left) leftPoint = min(leftPoint, x[r + 1] - h);
	    leftPoint = min(leftPoint, x[r + 1]);
	    dp[l][r][right][left] += toRight * (max(0, (leftPoint - x[l])) + f(L[l] + 1, r, 1, left));

	    // Fall to Left (Right Tree)
	    int rightPoint = x[R[r]] - h;
	    if(right) rightPoint = max(rightPoint, x[l - 1] + h);
	    rightPoint = max(rightPoint, x[l - 1]);
	    dp[l][r][right][left] += toLeft * (max(0, (x[r] - rightPoint)) + f(l, R[r] - 1, right, 1));
	    
	    // Fall to Right (Right Tree)
	    if(left) dp[l][r][right][left] += toRight * (min(max(0, x[r + 1] - x[r] - h), h) + f(l, r - 1, right, 0));
	    else dp[l][r][right][left] += toRight * (min(x[r + 1] - x[r], h) + f(l, r - 1, right, 0));
	}
    }
    return dp[l][r][right][left];
}

double solve() {
    sort(x + 1, x + 1 + n);
    
    x[n + 1] = INF;
    x[0] = -INF;

    for(int i = 1; i <= n; ++i) {
	int j = i;
	while(j + 1 <= n && x[j + 1] - x[j] < h) ++j;
	L[i] = j;

	j = i;
	while(j - 1 >= 1 && x[j] - x[j - 1] < h) --j;
	R[i] = j;
    }

    return f(1, n, 0, 0);
}

int main() {
    cin.sync_with_stdio(false);

    cin >> n >> h >> p;
    for(int i = 1; i <= n; ++i) cin >> x[i];

    cout << fixed << setprecision(10) << solve() << '\n';
    return 0;
}
