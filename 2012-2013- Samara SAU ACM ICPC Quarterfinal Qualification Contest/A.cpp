#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr,args)

const int maxn = 2500 + 10;

int n, m, q;
char c[maxn][maxn];

int row[maxn][maxn];
int col[maxn][maxn];

inline void compute()
{
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			row[i][j] = row[i][j - 1] + (c[i - 1][j - 1] != '#');

	for(int j = 1; j <= m; ++j)
		for(int i = 1; i <= n; ++i)
			col[j][i] = col[j][i - 1] + (c[i - 1][j - 1] != '#');

}

inline int Row(int r, int i, int j) { return row[r][j] - row[r][i - 1]; }
inline int Col(int c, int i, int j) { return col[c][j] - col[c][i - 1]; }

inline bool can(int &r1, int &c1, int &r2, int &c2)
{
	int cmin = min(c1,c2);
	int cmax = max(c1,c2);
	int rmin = min(r1,r2);
	int rmax = max(r1,r2);
	if(r1 == r2) return Row(r1, cmin, cmax) == cmax - cmin + 1;
	if(c1 == c2) return Col(c1, rmin, rmax) == rmax - rmin + 1;

	if(r1 > r2) swap(r1,r2), swap(c1,c2);

	if(Col(c1, rmin, rmax) == rmax - rmin + 1 && Row(r2, cmin, cmax) == cmax - cmin + 1) return true;
	if(Col(c2, rmin, rmax) == rmax - rmin + 1 && Row(r1, cmin, cmax) == cmax - cmin + 1) return true;
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);

	for(int i = 0; i < n; ++i) scanf(" %s", c[i]);

	compute();

	scanf("%d",&q);

	while(q--)
	{
		int r1,c1,r2,c2;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		if(can(r1,c1,r2,c2)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
