#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 2e4 + 10;
const int LOG = 20;

int n, m;
vector<int> adj[maxn];

int h[maxn];
int dp[LOG][maxn];
vector<pii> E;

int st[maxn], ed[maxn], cur;

void dfs(int v) {
    st[v] = ++cur;
    for(auto u: adj[v]) {
	if(u == dp[0][v]) continue;
	h[u] = h[v] + 1;
	dp[0][u] = v;
	dfs(u);
    }
    ed[v] = ++cur;
}

int lca(int x, int y) {
    if(h[y] < h[x]) swap(x, y);
    int d = h[y] - h[x];
    for(int k = LOG - 1; k >= 0; --k)
	if((1 << k) & d)
	    y = dp[k][y];
    if(x == y) return x;
    for(int k = LOG - 1; k >= 0; --k)
	if(dp[k][x] != dp[k][y]) {
	    x = dp[k][x];
	    y = dp[k][y];
	}
    return dp[0][x];
}

int pre[maxn + maxn];

ll solve() {
    dp[0][1] = 1;
    dfs(1);
    for(int k = 1; k < LOG; ++k)
	for(int i = 1; i <= n; ++i)
	    dp[k][i] = dp[k - 1][dp[k - 1][i]];
    for(auto e: E) {
	int u = e.first;
	int v = e.second;
	int c = lca(u, v);
	if(c == u) ++pre[ed[v]], --pre[st[c]];
	else if(c == v) ++pre[ed[u]], --pre[st[c]];
	else {
	    pre[st[c]] -= 2;
	    ++pre[ed[v]];
	    ++pre[ed[u]];
	}
    }
    for(int i = 1; i <= n + n; ++i)
	pre[i] += pre[i - 1];
    ll ans = 0;
    int notTree = m - (n - 1);
    for(int i = 2; i <= n; ++i) {
	int edges = pre[ed[i]] - pre[st[i] - 1];
	if(!edges) ans += notTree;
	else if(edges == 1) ++ans;
    }
    return ans;
}

int main() {
    freopen("diversion.in", "r", stdin);
    freopen("diversion.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if(c) {
	    adj[a].push_back(b);
	    adj[b].push_back(a);
	}
	else {
	    E.push_back({a, b});
	}
    }
    printf("%lld\n", solve());
    return 0;
}
