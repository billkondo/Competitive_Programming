#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

const int maxn = 2e2 + 10;
const int MAXN = 4e4 + 10;
const int maxLen = 1e6 + 10;

int n, m, q;
char grid[maxn][maxn];

char s[maxLen];

int a[15], b[15];

vector<int> adj[MAXN];
int go[MAXN];

int getID(int x, int y) { return x * m + y; }

int cntTree;
struct tree {
    bool digit[10];
    vector<int> nodesInCicle;
} T[MAXN];

bool inCicle[MAXN];

struct dsu {
    int par[MAXN];
    int sz[MAXN];

    void init() {
	for(int i = 0; i < n * m; ++i) {
	    par[i] = i;
	    sz[i] = 1;
	}
    }
    
    int root(int v) {
	if(par[v] == v) return v;
	return par[v] = root(par[v]);
    }

    void merge(int x, int y) {
	x = root(x);
	y = root(y);
	if(x == y) return;
	if(sz[y] > sz[x]) swap(x, y);
	sz[x] += sz[y];
	par[y] = x;
    }
} Tree;

void dfs0(int v, int root) {
    int x = v / m;
    int y = v % m;
    int d = grid[x][y] - '0';

    T[cntTree].digit[d] = true;
    inCicle[v] = true;
    T[cntTree].nodesInCicle.push_back(v);

    if(go[v] != root) dfs0(go[v], root);
}

void build() {
    for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j) {
	    int d = grid[i][j] - '0';
	    int x = i + a[d];
	    int y = j + b[d];

	    int u = getID(i, j);
	    if(x < 0 || x >= n || y < 0 || y >= m) go[u] = u;
	    else {
		int v = getID(x, y);
		go[u] = v;
		adj[v].push_back(u);
	    }
	}

    Tree.init();
    
    for(int i = 0; i < n * m; ++i) 
	if(Tree.root(i) == Tree.root(go[i])) {
	    ++cntTree;
	    dfs0(i, i);
	}
	else Tree.merge(i, go[i]);
}

int dp[MAXN];
int sz;
int is[10][maxLen];

void dfs(int u) {
    dp[u] = 0;

    int x = u / m;
    int y = u % m;

    for(auto v: adj[u])
	if(!inCicle[v]) {
	    dfs(v);
	    dp[u] = max(dp[u], dp[v]);
	}
    
    if(dp[u] < sz && s[dp[u]] == grid[x][y]) ++dp[u];
}

bool solve() {
    sz = strlen(s);

    for(int i = 0; i < 10; ++i) is[i][sz] = 0;

    for(int i = sz - 1; i >= 0; --i) {
	for(int k = 0; k < 10; ++k) is[k][i] = is[k][i + 1];
	int d = s[i] - '0';
	is[d][i] = 1;
    }
    
    for(int i = 1; i <= cntTree; ++i) {
	int Max = 0;

	for(auto u: T[i].nodesInCicle) {
	    dfs(u);
	    Max = max(Max, dp[u]);
	}

	bool ok = true;

	for(int k = 0; k < 10; ++k)
	    if(is[k][Max] && !T[i].digit[k])
		ok = false;
	
	if(ok) return true;
    }

    return false;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 0; i < n; ++i) scanf(" %s", grid[i]);
    for(int i = 0; i < 10; ++i) scanf("%d %d", &a[i], &b[i]);
    build();
    while(q--) {
	scanf(" %s", s);
	if(solve()) printf("YES\n");
	else printf("NO\n");
    }
    return 0;
}
