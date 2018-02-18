#include "bits/stdc++.h"
using namespace std;

const int N = 22;

int n, m;
int adj[N];

int dp[1 << N];
int go[1 << N];

vector<int> ans;

int f(int mask) {
    if(dp[mask] == -1) {
	if(mask == (1 << n) - 1) return dp[mask] = 0;
	dp[mask] = INT_MAX;
	for(int i = 0; i < n; ++i)
	    if((1 << i) & mask) {
		if((adj[i] | mask) != mask)
		    if(f(mask | adj[i]) + 1 < dp[mask]) {
			dp[mask] = f(mask | adj[i]) + 1;
			go[mask] = i;
		    }
	    }
    }
    return dp[mask];
}

void solve() {
    if(n * (n - 1) / 2 == m) return;
    memset(dp, -1, sizeof(dp));
    int Min = f(1);
    int start = 0;
    for(int i = 1; i < n; ++i)
	if(f(1 << i) < Min) {
	    Min = f(1 << i);
	    start = i;
	}

    int mask = (1 << start);
    while(mask != (1 << n) - 1) {
	int nx = go[mask];
	ans.push_back(nx + 1);
	mask |= adj[nx];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) {
	int u, v;
	scanf("%d %d", &u, &v);
	--u, --v;
	adj[u] += (1 << v);
	adj[v] += (1 << u);
    }
    solve();
    printf("%d\n", (int)ans.size());
    for(auto i: ans) printf("%d ", i);
    return 0;
}
