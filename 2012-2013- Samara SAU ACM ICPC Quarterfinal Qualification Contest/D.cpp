#include "bits/stdc++.h"
using namespace std;

#define pb push_back
typedef long long ll;

const int maxn = 1e6 + 10;

int k;
vector <int> d;
int p[maxn], cur[maxn];

void gen() /* generate divisors */
{
	for(int i = 1; i <= k; ++i)
		if(k % i == 0) 
		{
			d.pb(i);
			cur[i] = d.size() - 1;
		}
}

ll dp[maxn];

ll f(int i)
{
	if(dp[i] == -1)
	{
		if(!i) return dp[i] = 1LL;
		dp[i] = 0LL;
		for(int j = 1; j <= i; ++j)
			if(d[i] % d[j] == 0)
				dp[i] += f(cur[d[i]/d[j]]);
	}
	return dp[i];
}

ll solve()
{
	memset(dp,-1,sizeof(dp));
	return f(d.size() - 1);
}

int main()
{
	cin >> k;
	gen();
	cout << solve() << '\n';
	return 0;
}