#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr,args)

const int MAXN = 25000 + 10;
const int maxn = 500 + 10;;

int n, m;
bool mrk[maxn][maxn];
int x1[MAXN], x2[MAXN], y1[MAXN], y2[MAXN], area;

inline void add(int id){
	if(x1[id] == x2[id]){
		for(int i = min(y1[id],y2[id]); i <= max(y1[id],y2[id]) - 1; ++i){
			if(!mrk[x1[id]][i]) ++area;
			mrk[x1[id]][i] = true;
		}
	}
	else
		if(y1[id] == y2[id]){
			for(int i = min(x1[id],x2[id]); i <= max(x1[id],x2[id]); ++i){
				if(!mrk[i][y1[id]]) ++area;
				mrk[i][y1[id]] = true;
			}
	}
}

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int total;

inline void dfs(int i, int j){
	mrk[i][j] = true;
	++total;
	debug("%d %d\n", i, j);
	for(int k = 0; k < 4; ++k){
		int x = i + dx[k];
		int y = j + dy[k];
		if(x < 0 || x > 500 || y < 0 || y > 500 || mrk[x][y]) continue;
		dfs(x,y);
	}
}

int X1[MAXN], X2[MAXN], Y1[MAXN], Y2[MAXN]; 

inline int solve(){
	debug("call dfs()\n");
	dfs(0,0);
	debug("solve()\n");
	int city = 499 * 499 - area - total;
	area = 0;
	memset(mrk,false,sizeof(mrk));
	for(int i = 0; i < n; ++i) add(i);
	for(int i = 0; i < m; ++i){
		if(X1[i] == X2[i]){
			int l = min(Y1[i],Y2[i]);
			int r = max(Y1[i],Y2[i]);
			mrk[X1[i]][r - 1] = true;
		}
		else
			if(Y1[i] == Y2[i]){
				int l = min(X1[i],X2[i]);
				int r = max(X1[i],X2[i]);
				mrk[l][Y1[i]] = true;
			}
	}
	dfs(0,0);
	return (499 * 499 - area - total) - city;
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; ++i){
		scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
		add(i);
	}
	scanf("%d",&m);
	for(int i = 0; i < m; ++i)
		scanf("%d%d%d%d",&X1[i],&Y1[i],&X2[i],&Y2[i]);
	printf("%d\n",solve());
	return 0;
}