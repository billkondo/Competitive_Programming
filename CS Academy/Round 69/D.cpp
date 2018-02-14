#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;
const int maxn = 1e5 + 10;

int n;
vector<int> adj[maxn];

int root = -1;
int total = INT_MAX;
vector<pii> ans;

int dp[maxn];
int c[maxn];

void dfs0(int v, int par) {
    for(auto u: adj[v]) {
	if(u == par) continue;
	dfs0(u, v);
	++c[v];
	dp[v] += dp[u];
    }
    if(v != 1) dp[v] += (1 - c[v] % 2);
    else dp[v] += c[v] % 2;
}

void dfs1(int v, int par) {
    if(dp[v] < total) {
	total = dp[v];
	root = v;
    }

    for(auto u: adj[v]) {
	if(u == par) continue;

	int DPu = dp[u];
	int DPv = dp[v];
	int SONu = c[u];
	int SONv = c[v];

	dp[v] -= dp[u];
	dp[u] -= (1 - c[u] % 2);
	++c[u];
	dp[v] -= c[v] % 2;
	--c[v];

	dp[v] += (1 - c[v] % 2);

	dp[u] += dp[v];
	dp[u] += c[u] % 2;

	dfs1(u, v);

	dp[v] = DPv;
	c[v] = SONv;
	dp[u] = DPu;
	c[u] = SONu;
    }
}

void findRoot() {
    dfs0(1, -1);
    dfs1(1, -1);
}

int par[maxn];
int deg[maxn];

void dfs(int v) {
    for(auto u: adj[v])
	if(u != par[v]) {
	    par[u] = v;
	    dfs(u);
	    ++deg[v];
	}
}

vector<int> nodes[maxn];
queue<int> Q;

void solve() {
    if(n == 2) {
	ans.push_back({1, 2});	return;
    }
    
    findRoot();
    dfs(root);

    for(int i = 1; i <= n; ++i)
	if(!deg[i]) {
	    Q.push(i);
	    nodes[i].push_back(i);
	}

    while(!Q.empty()) {
	int v = Q.front();
	Q.pop();

	if(par[v]) --deg[par[v]];

	while(nodes[v].size() >= 2) {
	    int x = nodes[v].back();
	    nodes[v].pop_back();
	    int y = nodes[v].back();
	    nodes[v].pop_back();
	    ans.push_back({x, y});
	}

	if(nodes[v].size() == 1) {
	    if(par[v]) nodes[par[v]].push_back(nodes[v].back());
	    else ans.push_back({v, nodes[v].back()});
	}
	else if(par[v]) nodes[par[v]].push_back(v);

	if(par[v] && !deg[par[v]]) Q.push(par[v]);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n - 1; ++i) {
	int u, v;
	scanf("%d %d", &u, &v);
	adj[u].push_back(v);
	adj[v].push_back(u);
    }
    solve();
    printf("%d\n", (int)ans.size());
    for(auto p: ans) printf("%d %d\n", p.first, p.second);
    return 0;
}
