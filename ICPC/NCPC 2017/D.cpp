#include "bits/stdc++.h"
using namespace std; 

const int K = 21;
const int maxn = 1 << K;

int n, k;
queue<int> Q;
int dis[maxn];

vector<int> adj[maxn];

void build() {
    memset(dis, -1, sizeof(dis));
    for(int i = 1; i <= (1 << k); ++i) {
	for(int j = 0; j < k; ++j)
	    if((1 << j) & i) {
		adj[i].push_back(i - (1 << j));
		adj[i - (1 << j)].push_back(i);
	    }
    }
}

int ans[K];
int dist = -1;
int cur = -1;

void bfs() {
    while(!Q.empty()) {
	int v = Q.front();
	Q.pop();
	for(auto u: adj[v])
	    if(dis[u] ==-1) {
		dis[u] = dis[v] + 1;
		Q.push(u);
	    }
    }
    for(int i = 1; i <= (1 << k); ++i)
	if(dis[i] > dist) {
	    dist = dis[i];
	    cur = i;
	}
    for(int i = 0; i < k; ++i)
	if((1 << i) & cur)
	    ans[i] = 1;
}

int main() {
    scanf("%d %d", &n, &k);
    build();
    for(int i = 1; i <= n; ++i) {
	char s[K];
	scanf(" %s", s);
	int node = 0;
	for(int j = 0; j < k; ++j)
	    if(s[j] == '1')
		node += (1 << j);
	dis[node] = 0;
	Q.push(node);
    }
    bfs();
    for(int i = 0; i < k; ++i)
	printf("%d", ans[i]);
    return 0;
}
