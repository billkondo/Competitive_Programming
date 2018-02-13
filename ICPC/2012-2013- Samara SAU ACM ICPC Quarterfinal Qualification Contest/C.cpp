#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 3e2 + 10;

int n;
ll d[maxn][maxn], save[maxn][maxn];

bool solve()
{
	for(int k = 1; k <= n; ++k)
		for(int a = 1; a <= n; ++a)
			for(int b = 1; b <= n; ++b)
				d[a][b] = min(d[a][b],d[a][k] + d[k][b]);

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(d[i][j] != save[i][j])
				return false;

	return true;
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> d[i][j], save[i][j] = d[i][j];
		
	if(solve())
	{
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j) 
				cout << save[i][j] << " ";
			cout << '\n';
		}
	}
	else cout << "-1\n";
	
	return 0;
}
