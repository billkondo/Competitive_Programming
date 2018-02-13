#include "bits/stdc++.h"
using namespace std;

const int MAXN = 2e5 + 10;

int T;

int n, c[MAXN];

vector <int> adj[MAXN];

int C[MAXN];

int dis[MAXN];

int bfs() {
  for(int i = 1; i <= n; ++i)
    dis[i] = -1;
  
  queue <int> Q;
  dis[1] = 0;
  Q.push(1);
  
  while(!Q.empty()) {
    int v = Q.front();
    Q.pop();

    for(int i = 0; i < adj[v].size(); ++i) {
      int u = adj[v][i];

      if(dis[u] == -1) {
	dis[u] = dis[v] + 1;
	Q.push(u);
      }
    }
  }

  return dis[n];
}

int solve() {
  for(int i = 1; i <= n; ++i) {
    adj[i].clear();
    C[c[i]] = -1;
  }

  for(int i = n; i >= 1; --i) {
    if(i + 1 <= n)
      adj[i].push_back(i + 1);

    if(C[c[i]] != -1)
      adj[i].push_back(C[c[i]]);

    C[c[i]] = i;
  }

  return bfs();
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
      scanf("%d", &c[i]);

    printf("%d\n", solve());
  }
  
  return 0;
}
