#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const int maxn = 1e2 + 10;

int T, n;
ll K;

vector<pii> adj[maxn];

void addEdge(int x, int y, int id) {
    adj[x].push_back(pii(y, id));
}

int mrk[maxn];
int sz;
vector<int> stk;

ll ans;
int cicle;

void dfs(int u, int par) {
    stk.push_back(u);
    mrk[u] = 1;
    ++sz;

    for(int i = 0; i < adj[u].size(); ++i) {
	int v = adj[u][i].first;
	int id = adj[u][i].second;
	if(id == par) continue;
	if(!mrk[v]) dfs(v, id);
	else if(mrk[v] == 1) {
	    for(int k = (int)stk.size() - 1; k >= 0; --k) {
		int x = stk[k];
		++cicle;
		if(x == v) break;
	    }
	}
    }
    
    mrk[u] = 2;
    stk.pop_back();
}

ll dp[maxn][2];

ll f(int len, int flag) {
    if(dp[len][flag] == -1) {
	if(len == 1) return dp[len][flag] = flag ? 0 : 1LL;
	if(flag) dp[len][flag] = ((K - 1) * f(len - 1, 0)) % mod;
	else {
	    dp[len][flag] = f(len - 1, 1);
	    dp[len][flag] = (dp[len][flag] + (K - 2) * f(len - 1, 0)) % mod;
	}
    }
    return dp[len][flag];
}

ll solve() {
    ans = 1LL;

    memset(dp, -1, sizeof(dp));

    for(int i = 0; i < n; ++i) mrk[i] = 0;

    for(int i = 0; i < n; ++i)
	if(!mrk[i]) {
	    sz = 0;
	    cicle = 0;
	    dfs(i, -1);

	    ll add = (K * (K - 1) * f(cicle - 1, 0)) % mod;
	    	
	    for(int k = 1; k <= sz - cicle; ++k)
		add = (add * (K - 1)) % mod;

	    ans = (ans * add) % mod;
	}

    return ans;
}

int main() {
    cin.sync_with_stdio(false);

    cin >> T;

    while(T--) {
	cin >> n >> K;
	for(int i = 0; i < n; ++i) adj[i].clear();
	for(int i = 0; i < n; ++i) {
	    int nx;
	    cin >> nx;
	    addEdge(i, nx, i);
	    addEdge(nx, i, i);
	}
	cout << solve() << '\n';
    }
    return 0;
}

