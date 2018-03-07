#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1e6 + 10;

int n, m, start;

int curTime;
int h[maxn], low[maxn];
int used[maxn];
vector<int> stk;

int cntComp;
int id[maxn];

vector<int> adj[maxn];

void dfs(int u) {
    used[u] = 1;
    low[u] = h[u] = ++curTime;
    stk.push_back(u);

    for(auto v: adj[u])
	if(!used[v]) {
	    dfs(v);
	    low[u] = min(low[u], low[v]);
	}
	else if(used[v] == 1) low[u] = min(low[u], h[v]);
    
    if(low[u] == h[u]) {
	++cntComp;
	while(!stk.empty()) {
	    int v = stk.back();
	    stk.pop_back();
	    id[v] = cntComp;
	    used[v] = 2;
	    if(v == u) break;
	}
    }
}

struct edge {
    int x, y;
    ll c;
};

vector<edge> edges;

vector<int> dag[maxn];
vector<ll> costDag[maxn];

ll sum[maxn];
ll f[maxn];

ll getCost(ll x) {
    int l = 0;
    int r = maxn;
   
    while(l < r) {
	int mid = (l + r + 1) >> 1;
	ll cmp = 1LL * mid * (mid + 1) / 2LL;
	if(cmp < x) l = mid;
	else r = mid - 1;
    }
    
    return (r + 1) * x - f[r];    
}

ll dp[maxn];

ll get(int u) {
    if(dp[u] == -1) {
	dp[u] = 0;
	for(int i = 0; i < (int)dag[u].size(); ++i) {
	    int v = dag[u][i];
	    ll c = costDag[u][i];
	    dp[u] = max(dp[u], get(v) + c);
	}
	dp[u] += sum[u];
    }
    return dp[u];
}

ll solve() {
    for(int i = 1; i < maxn; ++i) f[i] = f[i - 1] + 1LL * i * (i + 1) / 2;
    
    for(auto e: edges) {
	int x = e.x;
	int y = e.y;
	adj[x].push_back(y);
    }
    
    for(int i = 1; i <= n; ++i)
	if(!used[i])
	    dfs(i);

    for(auto e: edges) {
	int x = id[e.x];
	int y = id[e.y];
	ll c = e.c;

	if(x == y) sum[x] += getCost(c);
	else {
	    dag[x].push_back(y);
	    costDag[x].push_back(c);
	}
    }

    memset(dp, -1, sizeof(dp));
    return get(id[start]);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) {
	int x, y;
	ll cost;
	scanf("%d %d %lld", &x, &y, &cost);
	edges.push_back({x, y, cost});
    }
    scanf("%d", &start);
    printf("%lld\n", solve());
    return 0;
}
