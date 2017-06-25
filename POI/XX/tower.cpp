#include "bits/stdc++.h"
using namespace std;

#define pb push_back
const int maxn = 5e5 + 10;

int n, m, k;
bool mrk[maxn];
vector<int>adj[maxn], ans;

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1; i <= m; ++i){
		int a, b;
		scanf("%d%d",&a,&b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(int v = 1; v <= n; ++v)
		if(!mrk[v]){
			ans.pb(v);
			mrk[v] = true;
			for(int i = 0; i < adj[v].size(); ++i){
				int u = adj[v][i];
				mrk[u] = true;
				for(int j = 0; j < adj[u].size(); ++j){
					int c = adj[u][j];
					mrk[c] = true;
				}
			} 
		}
	printf("%d\n",ans.size());
	for(int i = 0; i < ans.size(); ++i) printf("%d ",ans[i]);
	return 0;
}