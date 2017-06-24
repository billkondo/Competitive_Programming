#include "bits/stdc++.h"
using namespace std;

const int maxn = 2e5 + 10;

int n, p, q, c[maxn + maxn];

int cur;

int l[2][maxn + maxn];

inline void build()
{
	cur = n;
	for(int i = 1; i <= n; ++i)
	{
		if(i != 1) l[0][i] = i - 1;
		else l[0][i] = -1;

		if(i != n) l[1][i] = i + 1;
		else l[1][n] = -1;
	}
}

int main()
{
	scanf("%d%d",&n,&p);
	for(int i = 1; i <= n; ++i) scanf("%d",&c[i]);
	build();
	scanf("%d",&q);
	int pointer = p; 
	while(q--)
	{
		char s[20];
		scanf(" %s", s);

		if(s[0] == 'p')
		{ 
			printf("%d\n",c[pointer]); 
			continue; 
		}

		if(s[4] == 'L')
			if(l[0][pointer] != -1) 
			{
				pointer = l[0][pointer];
				continue;
			}
		
		if(s[4] == 'R')
			if(l[1][pointer] != -1) 
			{
				pointer = l[1][pointer];
				continue;
			}

		if(s[6] == 'L')
		{
			int x;
			scanf(" %d",&x);
			
			++cur;
			c[cur] = x;
			int pos = l[0][pointer];
			l[0][pointer] = cur;

			if(pos != -1) l[1][pos] = cur;

			l[0][cur] = pos;
			l[1][cur] = pointer;

			continue;
		}

		if(s[6] == 'R')
		{
			int x;
			scanf(" %d",&x);

			++cur;
			c[cur] = x;
			int pos = l[1][pointer];
			l[1][pointer] = cur;

			if(pos != -1) l[0][pos] = cur;

			l[0][cur] = pointer;
			l[1][cur] = pos;
		}
	}
	return 0;
}