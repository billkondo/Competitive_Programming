#include "bits/stdc++.h"
using namespace std;

const int maxn = 5e2 + 10;
const int INF = 1e8;

int n, m, k;
char s[maxn][maxn];

int dp[maxn][maxn];
int cost[maxn][maxn];
int cnt[maxn];

int g(int day, int x) {
    if(cost[day][x] == -1) {
	if(!x) return cost[day][x] = 0;
	if(x == 1) return cost[day][x] = 1;
	cost[day][x] = INF;
	int l = 0;
	int count = 0;
	for(int i = 0; i < m; ++i) {
	    if(s[day][i] == '1') ++count;
	    while(count > x) {
		if(s[day][l] == '1') --count;
		++l;
	    }
	    while(s[day][l] == '0') ++l;
	    if(count == x) cost[day][x] = min(cost[day][x], i - l + 1);
	}
	    
    }
    return cost[day][x];
}

int f(int day, int left) {
    if(dp[day][left] == -1) {
	if(day >= n) return dp[day][left] = 0;
	dp[day][left] = INF;
	for(int take = cnt[day]; take >= max(0, cnt[day] - left); --take)
	    dp[day][left] = min(dp[day][left], f(day + 1, left - (cnt[day] - take)) + g(day, take));
    }
    return dp[day][left];
}

int solve() {
    memset(dp, -1, sizeof(dp));
    memset(cost, -1, sizeof(cost));
    for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
	    if(s[i][j] == '1')
		++cnt[i];
    return f(0, k);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i < n; ++i) scanf(" %s", s[i]);
    printf("%d\n", solve());
    return 0;
}
