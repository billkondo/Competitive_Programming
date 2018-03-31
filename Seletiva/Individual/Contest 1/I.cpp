#include "bits/stdc++.h"
using namespace std;

#define debug(args...) //fprintf(stderr, args);

const int maxn = 55;
const int MAX = 5e3 + 10;
const int INF = 0x3f3f3f3f;

char s[2][maxn];

int cur[2];
int L[2][maxn], R[2][maxn];
int type[2][maxn];
vector<int> heads[2][maxn], tails[2][maxn], adj[2][maxn];
int End[2];

inline int createNode(int k) {
    int u = ++cur[k];
    L[k][u] = R[k][u] = 0;
    type[k][u] = 0;
    heads[k][u].clear();
    tails[k][u].clear();
    adj[k][u].clear();
    return u;
}

inline void parsing(int k) {
    int n = strlen(s[k]);
    vector<int> stk;
    cur[k] = 0;
    
    debug("processing %s\n", s[k]);

    for(int i = 0; i < n; ++i) {
	char c = s[k][i];

	if(c == '(') {
	    int u = createNode(k);

	    if(!stk.empty()) {
		int v = stk.back();

		if(!L[k][v]) L[k][v] = u;
		else R[k][v] = u;
	    }
		    
	    stk.push_back(u);
	}
	else
	    if(c == '*' || c == '|') {
		int id = (c == '|') ? 1 : 2;
		int v = stk.back();
		type[k][v] = id;
	    }
	    else
		if(c == ')') {
		    int v = stk.back();
		    stk.pop_back();

		    if(type[k][v] == 2) {
			int l = L[k][v];
						
			tails[k][v] = tails[k][l];
			heads[k][v] = heads[k][l];
						
			for(auto x: heads[k][v])
			    for(auto y: tails[k][v])
				adj[k][x].push_back(y);
		    }
		    else
			if(type[k][v] == 1) {
			    int l = L[k][v];
			    int r = R[k][v];

			    assert(l && r);

			    heads[k][v] = heads[k][l];
			    tails[k][v] = tails[k][l];
			    for(auto x: heads[k][r]) heads[k][v].push_back(x);
			    for(auto x: tails[k][r]) tails[k][v].push_back(x);

			    if(type[k][l] == 2 || type[k][r] == 2) type[k][v] = 2;
			}
			else {
			    int l = L[k][v];
			    int r = R[k][v];

			    assert(l && r);

			    for(auto x: heads[k][l])
				for(auto y: tails[k][r])
				    adj[k][x].push_back(y);

			    tails[k][v] = tails[k][l];
			    heads[k][v] = heads[k][r];

			    if(type[k][r] == 2) 
				for(auto x: heads[k][l]) heads[k][v].push_back(x);

			    if(type[k][l] == 2)
				for(auto x: tails[k][r]) tails[k][v].push_back(x);

			    if(type[k][l] == 2 && type[k][r] == 2) type[k][v] = 2;
			}
		}
		else {
		    int u = createNode(k);

		    if(!stk.empty()) {
			int v = stk.back();

			if(!L[k][v]) L[k][v] = u;
			else R[k][v] = u;
		    }

		    int id = (c - 'a') + 3;
		    type[k][u] = id;

		    heads[k][u].push_back(u);
		    tails[k][u].push_back(u);
		}
    }

    End[k] = createNode(k);
    for(auto x: heads[k][1]) adj[k][x].push_back(End[k]);
    if(type[k][1] == 2) tails[k][1].push_back(End[k]);

    debug("start: ");
    for(auto x: tails[k][1]) debug("%d ", x);
    debug("\n");
    for(int v = 1; v <= cur[k]; ++v) {
	debug("%d %d --", v, type[k][v]);
	for(auto x: adj[k][v]) debug("%d ", x);
	debug("\n");
    }
}

int dp[maxn][maxn][MAX];

int f(int u, int v, int walk) {
    if(dp[u][v][walk] == -1) {
	dp[u][v][walk] = INF;
	if(walk == MAX - 1) return dp[u][v][walk];
	if(u == End[0] && v == End[1]) return dp[u][v][walk] = 0;
	for(auto x: adj[0][u]) dp[u][v][walk] = min(dp[u][v][walk], f(x, v, walk + 1) + 1);
	for(auto y: adj[1][v]) dp[u][v][walk] = min(dp[u][v][walk], f(u, y, walk + 1) + 1);
	for(auto x: adj[0][u])
	    for(auto y: adj[1][v])
		dp[u][v][walk] = min(dp[u][v][walk], f(x, y, walk + 1) + (type[0][u] != type[1][v]));
    }
    return dp[u][v][walk];
}

inline int solve() {
    for(int k = 0; k <= 1; ++k) parsing(k);
    int ans = INF;
    memset(dp, -1, sizeof(dp));
    for(auto x: tails[0][1])
	for(auto y: tails[1][1]) 
	    ans = min(ans, f(x, y, 0));
    assert(ans != INF);
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
	scanf(" %s %s", s[0], s[1]);
	printf("%d\n", solve());
    }
    return 0;
}
