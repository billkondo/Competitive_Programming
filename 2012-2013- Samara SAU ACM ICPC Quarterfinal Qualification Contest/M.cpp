#include "bits/stdc++.h"
using namespace std;

const int maxn = 2e5 + 10;

int n, c[maxn];

set <int> pos[maxn];

int dp[maxn];

int f(int i)
{
	if(dp[i] == -1)
	{
		if(i == n) return dp[i] = 0;
		dp[i] = f(i + 1) + 1;
		set <int> :: iterator it = pos[c[i]].upper_bound(i);
		if(it != pos[c[i]].end()) dp[i] = min(dp[i],f((*it)) + 1);
	}
	return dp[i];
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> c[i], pos[c[i]].insert(i);
	memset(dp,-1,sizeof(dp));
	cout << f(1) << '\n';
	
	return 0;
}
