#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define debug(args...) fprintf(stderr,args)
const int maxn = 5e3 + 10;
const int INF = 3e4;

int n, m, q;

vector<int>adj[maxn];

short dis[2][maxn][maxn];

struct tp{
	int v, dis, type;
	tp(int v, int dis, int type) : v(v), dis(dis), type(type) {}
};

void bfs(int root){
	for(int i = 1; i <= n; ++i) dis[0][root][i] = dis[1][root][i] = INF;
	queue<tp>Q;
	dis[0][root][root] = 0;
	Q.push(tp(root,0,0));
	while(!Q.empty()){
		int v = Q.front().v;
		int id = Q.front().type;
		Q.pop();
		for(int i = 0; i < adj[v].size(); ++i){
			int u = adj[v][i];
			if(dis[id ^ 1][root][u] == INF){
				dis[id ^ 1][root][u] = dis[id][root][v] + 1;
				Q.push(tp(u,dis[id ^ 1][root][u],id ^ 1));
			}
		}
	}
}

void compute(){
	for(int v = 1; v <= n; ++v) bfs(v);
}

bool can(int s, int t, int c){
	if(adj[s].empty()) return false;
	
	int d1 = (int)dis[0][s][t];
	int d2 = (int)dis[1][s][t];

	if(d1 != INF && d1 <= c){
		int x = c - d1;
		if(x % 2 == 0) return true;
	}

	if(d2 != INF && d2 <= c){
		int x = c - d2;
		if(x % 2 == 0) return true;
	}

	return false;
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1; i <= m; ++i)
	{
		int a, b;
		scanf("%d%d",&a,&b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	compute();
	while(q--)
	{
		int s, t, c;
		scanf("%d%d%d",&s,&t,&c);
		if(can(s,t,c)) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}