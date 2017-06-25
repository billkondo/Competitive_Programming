#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e2 + 10;
int n, a[maxn];

set <int> lose;

void compute()
{
	long long cur = 1;

	while(cur <= 1e9)
	{
		lose.insert(cur);
		cur *= 2LL;
		++cur;
	}
}

bool solve()
{
	int maior = 0;
	for(int i = 1; i <= n; ++i) maior = max(maior, a[i]);
	if(lose.find(maior) != lose.end()) return false;
	return true;
}

int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
	compute();
	if(solve()) printf("Constantine\n");
	else printf("Mike\n");
	
	return 0;
}
