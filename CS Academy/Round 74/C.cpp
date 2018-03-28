#include "bits/stdc++.h"
using namespace std;

#define debug(args...) //fprintf(stderr, args)

const int maxn = 2e2 + 10;

int n, m, k;
int a[maxn][maxn];

int pre[maxn][maxn];

void compute() {
    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
	    pre[i][j] = a[i][j];
    
    for(int i = 1; i <= n; ++i) 
	for(int j = 1; j <= m; ++j)
	    pre[i][j] += pre[i][j - 1];

    for(int j = 1; j <= m; ++j)
	for(int i = 1;  i <= n; ++i)
	    pre[i][j] += pre[i - 1][j];
}

int val[maxn][maxn];

inline int get(int i, int j) {
    int x = i - k + 1;
    int y = j - k + 1;
    if(x <= 0 || y <= 0) return INT_MIN;
    return pre[i][j] + pre[x - 1][y - 1] - pre[i][y - 1] - pre[x - 1][j];
}

inline int rect(int x1, int y1, int x2, int y2) {
    if(x1 <= 0 || y1 <= 0) return INT_MIN;
    return pre[x2][y2] + pre[x1 - 1][y1 - 1] - pre[x2][y1 - 1] - pre[x1 - 1][y2];
}

int DOWN[maxn];
int RIGHT[maxn];

int getMax() {
    int ans = 0;

    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
	    val[i][j] = get(i, j);

    debug("values\n");
    for(int i = 1; i <= n; ++i) {
	for(int j = 1; j <= m; ++j)
	    if(val[i][j] != INT_MIN)
		debug("%d ", val[i][j]);
	    else
		debug("INF ");
	debug("\n");
    }

    for(int i = n; i >= 1; --i) {
	int MAX = INT_MIN;
	for(int j = 1; j <= m; ++j)
	    MAX = max(MAX, val[i][j]);
	if(i == n) DOWN[i] = MAX;
	else DOWN[i] = max(DOWN[i + 1], MAX);
    }

    for(int j = m; j >= 1; --j) {
	int MAX = INT_MIN;
	for(int i = 1; i <= n; ++i)
	    MAX = max(MAX, val[i][j]);
	if(j == m) RIGHT[j] = MAX;
	else RIGHT[j] = max(RIGHT[j + 1], MAX);
    }

    for(int i = k; i <= n; ++i) {
	for(int j = k; j <= m; ++j) {
	    if(j + k <= m) ans = max(ans, val[i][j] + RIGHT[j + k]);
	    if(i + k <= n) ans = max(ans, val[i][j] + DOWN[i + k]);

	    int x = i - k + 1;
	    int y = j - k + 1;
	    int I = min(n, i + k - 1);
	    int J = min(m, j + k - 1);

	    for(int X = x; X <= I; ++X)
		for(int Y = y; Y <= J; ++Y) {
		    int x1, y1, x2, y2;
		    x1 = max(i - k + 1, X - k + 1);
		    y1 = max(j - k + 1, Y - k + 1);
		    x2 = min(i, X);
		    y2 = min(j, Y);
		    ans = max(ans, val[i][j] + val[X][Y] - rect(x1, y1, x2, y2));
		}
	    
	}
    }

    debug("ans = %d\n", ans);
    
    return ans;
}

int solve() {
    int zeros = 0;
    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
	    zeros += (a[i][j] == 0);
    compute();
    return zeros + getMax();
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
	    scanf("%d", &a[i][j]);

    printf("%d\n", solve());
    return 0;
}
