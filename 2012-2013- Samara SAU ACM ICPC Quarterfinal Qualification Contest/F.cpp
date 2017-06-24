#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr,args)

const int maxn = 2e5 + 10;

int n;

set <int> tree;
set <int> :: iterator L, R;

int h[maxn];

int main()
{
	scanf("%d",&n);
	tree.insert(0);
	tree.insert(n + 1);
	h[0] = h[n + 1] = INT_MIN;
	long long ans = 0LL;
	for(int i = 1; i <= n; ++i)
	{
		int p;
		scanf("%d",&p);
		tree.insert(p);
		if(tree.size() == 3)
		{
			h[p] = 1;
			continue;
		}
		L = --tree.find(p);
		R = ++tree.find(p);
		h[p] = max(h[*L],h[*R]) + 1;
		ans += h[p] - 1;
	}
	printf("%lld\n",ans);
	return 0;
}