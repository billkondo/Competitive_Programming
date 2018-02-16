#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 2e5 + 10;

int n, m;

ll dis[maxn];
vector<pii> adj[maxn];
bool mrk[maxn];

set<pii> Q;

void dijkstra() {
    for(int i = 1; i <= n; ++i)
	Q.insert({dis[i], i});
    
    while(!Q.empty()) {
	int v = Q.begin()->second;
	Q.erase(Q.begin());
	if(mrk[v]) continue;
	mrk[v] = true;
	for(auto i: adj[v]) {
	    ll w = i.first;
	    int u = i.second;
	    if(dis[u] > dis[v] + w) {
		dis[u] = dis[v] + w;
		Q.insert({dis[u], u});
	    }
	}
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) {
	int u, v;
	ll w;
	scanf("%d %d %lld", &u, &v, &w);
	adj[u].push_back({w + w, v});
	adj[v].push_back({w + w, u});
    }
    for(int i = 1; i <= n; ++i)
	scanf("%lld", &dis[i]);
    dijkstra();
    for(int i = 1; i <= n; ++i)
	printf("%lld ", dis[i]);
    return 0;
}
