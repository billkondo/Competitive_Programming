#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;

int n;
vector<int> adj[maxn];

int h[maxn];
int cnt[maxn];

void dfs(int v) {
    ++cnt[h[v]];
    for(auto u: adj[v]) {
	h[u] = h[v] + 1;
	dfs(u);
    }
}

int solve() {
    h[1] = 1;
    dfs(1);
    int ans = 0;
    for(int i = 1; i <= n; ++i) ans += (cnt[i] % 2);
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 2; i <= n; ++i) {
	int p;
	scanf("%d", &p);
	adj[p].push_back(i);
    }
    printf("%d\n", solve());
    return 0;
}
