#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 3e5 + 10;
const int INF = 1e8;

int n;
int N;

vector<int> adj[maxn];

int pairU[maxn];
int pairV[maxn];
int dist[maxn];

set<int> rec[maxn];

bool bfs() {
    queue<int> Q;
    for(int i = 1; i <= N; ++i)
	if(!pairU[i]) {
	    dist[i] = 0;
	    Q.push(i);
	}
	else dist[i] = INF;

    dist[0] = INF;

    while(!Q.empty()) {
	int u = Q.front();
	Q.pop();

	if(dist[u] < dist[0]) {
	    for(auto v: adj[u]) 
		if(dist[pairV[v]] == INF) {
		    dist[pairV[v]] = dist[u] + 1;
		    Q.push(pairV[v]);
		}
	    
	}
    }

    return dist[0] != INF;
}

bool dfs(int u) {
    if(u) {
	for(auto v: adj[u]) 
	    if(dist[pairV[v]] == dist[u] + 1) 
		if(dfs(pairV[v])) {
		    pairV[v] = u;
		    pairU[u] = v;
		    return true;
		}
	
	
	dist[u] = INF;
	return false;
    }

    return true;
}

int hopcroftKarp() {
    int ans = 0;

    while(bfs()) {
	for(int i = 1; i <= N; ++i)
	    if(!pairU[i] && dfs(i))
		++ans;
    }
    
    return ans;
}

struct line {
    int l, r, type;
};

vector<line> E[maxn];

ll seg[4 * maxn];
ll lazy[4 * maxn];

void refresh(int idx, int i, int j) {
    if(!lazy[idx]) return;

    int left = idx << 1;
    int right = left | 1;
    ll add = lazy[idx];
    
    if(i != j) {
	lazy[left] += add;
	lazy[right] += add;
    }

    seg[idx] += add * (j - i + 1);
    lazy[idx] = 0;
}

void update(int idx, int i, int j, int l, int r, int val) {
    refresh(idx, i, j);

    if(i > j || j < l || r < i) return;
    if(l <= i && j <= r) {
	lazy[idx] += val;
	refresh(idx, i, j);
	return;
    }

    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    update(left, i, mid, l, r, val);
    update(right, mid + 1, j, l, r, val);

    seg[idx] = seg[left] + seg[right];
}

int query(int idx, int i, int j, int l, int r) {
    refresh(idx, i, j);

    if(i > j || j < l || r < i || !seg[idx]) return N + 1;
    if(i == j) return i;

    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    int q = query(left, i, mid, l, r);

    if(q <= N) return q;
    return query(right, mid + 1, j, l, r);
}

void build() {
    for(int x = 1; x <= N; ++x) {
	for(auto e: E[x])
	    if(!e.type) update(1, 1, N, e.l, e.r, +1);
	    else update(1, 1, N, e.l, e.r, -1);

	int y = query(1, 1, N, 1, N);

	while(y <= N) {
	    adj[x].push_back(y);
	    y = query(1, 1, N, y + 1, N);
	}
    }
}

vector<int> G[maxn + maxn];
bool mrk[maxn + maxn];

void DFS(int u) {
    mrk[u] = true;
    for(auto v: G[u])
	if(!mrk[v])
	    DFS(v);
}

vector<int> row, col;

void get() {
    for(int u = 1; u <= N; ++u) {
	for(auto v: adj[u]) {
	    if(v == pairU[u]) continue;
	    G[u].push_back(v + N);
	}
	if(pairU[u]) G[pairU[u] + N].push_back(u);
    }

    for(int i = 1; i <= N; ++i)
	if(!pairU[i] && !mrk[i]) 
	    DFS(i);

    for(int i = 1; i <= N; ++i)
	if(!mrk[i])
	    col.push_back(i);

    for(int i = N + 1; i <= N + N; ++i)
	if(mrk[i])
	    row.push_back(i - N);
}

int main() {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i) {
	int x1, y1, x2, y2;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	++x1, ++y1, ++x2, ++y2;

	N = max(N, y2);
	N = max(N, x2);

	E[x1].push_back({y1, y2, 0});
	E[x2 + 1].push_back({y1, y2, 1});
    }

    build();

    printf("%d\n", hopcroftKarp());
    get();

    printf("%d\n", (int)col.size());
    for(auto i: col) printf("%d ", i - 1);
    printf("\n");

    printf("%d\n", (int)row.size());
    for(auto i: row) printf("%d ", i - 1);
    printf("\n");

    return 0;
}
