#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

const int maxn = 1e5 + 10;

int T;
int n, m;
vector<int> adj[maxn];

vector<int> stk;

int mrk[maxn];
int low[maxn], h[maxn], t;
int cur, id[maxn];

bool findOddCicle;

void dfs(int v) {
    low[v] = h[v] = ++t;
    mrk[v] = 1;
    stk.push_back(v);

    for(auto u: adj[v]) 
	if(!mrk[u]) {
	    dfs(u);
	    low[v] = min(low[v], low[u]);
	}
	else if(mrk[u] == 1) low[v] = min(low[v], h[u]);
    
    if(low[v] == h[v]) {
	++cur;
	while(!stk.empty()) {
	    int u = stk.back();
	    stk.pop_back();
	    id[u] = cur;
	    mrk[u] = 2;
	    if(u == v) break;
	}
    }
}

vector<int> ans;
int used[2][maxn];

void dfs(int c, int v) {
    used[c][v] = 1;
    stk.push_back(v);
    for(auto u: adj[v]) {
	int nx = c ^ 1;
	if(id[v] != id[u]) continue;
	if(!findOddCicle && used[c][u] == 1) {
	    findOddCicle = true;
	    ans.clear();
	    for(int k = stk.size() - 1; k >= 0; --k) {
		int node = stk[k];
		ans.push_back(node);
		if(node == u) break;
	    }
	    reverse(ans.begin(), ans.end());
	}
	if(!used[nx][u]) dfs(nx, u);
    }
    used[c][v] = 2;
    stk.pop_back();
}

bool solve() {
    cur = 0;
    t = 0;
    findOddCicle = false;

    for(int i = 1; i <= n; ++i)
	if(!mrk[i])
	    dfs(i);

    for(int i = 1; i <= cur; ++i) mrk[i] = 0;

    for(int i = 1; i <= n; ++i) {
	int x = id[i];
	if(mrk[x]) continue;
	mrk[x] = true;
	dfs(0, x);
    }

    return findOddCicle;
}

int main() {
    scanf("%d", &T);
    while(T--) {
	scanf("%d %d", &n, &m);

	for(int i = 1; i <= n; ++i) {
	    mrk[i] = 0;
	    adj[i].clear();
	    id[i] = -1;
	    used[0][i] = used[1][i] = 0;
	}

	for(int i = 1; i <= m; ++i) {
	    int x, y;
	    scanf("%d %d", &x, &y);
	    adj[x].push_back(y);
	}

	if(solve()) {
	    printf("1\n");
	    printf("%d\n", (int)ans.size());
	    for(int i = 0; i < ans.size(); ++i) printf("%d\n", ans[i]);
	}
	else 
	    printf("-1\n");
		
    }
    return 0;
}
