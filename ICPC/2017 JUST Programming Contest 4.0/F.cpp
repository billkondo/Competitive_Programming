#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

typedef pair <int, int> pii;

const int LEN = 30 + 10;
const int MAXN = 1e4 + 10;
const int K = 15;

int T;
int n, q;

int cur;
unordered_map <string, int> M;

int cost[MAXN];

int dp[LEN][LEN];
string s;

inline void calc(int id) {
  int N = (int)s.size();

  for(int i = 0; i < N; ++i) {
    dp[i][i] = 1;

    if(i + 1 < N) {
      if(s[i] != s[i + 1])
	dp[i][i + 1] = 0;
      else
	dp[i][i + 1] = 1;
    }
  }

  for(int l = 3; l <= N; ++l)
    for(int i = 0; i + l - 1 < N; ++i) {
      int j = i + l - 1;
      dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
    }

  cost[id] = 0;
  for(int i = 0; i < N; ++i)
    for(int j = i; j < N; ++j)
      cost[id] += dp[i][j];
}

pii rmq[K][MAXN];
int pot[MAXN];

inline void build() {
  for(int i = 1; i <= n; ++i) 
    rmq[0][i] = {cost[i], -i};

  for(int k = 1; k < K; ++k)
    for(int i = 1; i <= n; ++i)
      rmq[k][i] = max(rmq[k - 1][i], rmq[k - 1][min(n, i + (1 << (k - 1)))]);
}

inline int query(int l, int r) {
  int len = r - l + 1;
  int k = pot[len];

  return -max(rmq[k][l], rmq[k][r - (1 << k) + 1]).second;
}

int main() {
  cin.sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> T;

  for(int i = 1; i < MAXN; ++i)
    pot[i] = (int)log2(i);

  while(T--) {
    cin >> n >> q;

    M.clear();
    cur = 0;
    
    for(int i = 1; i <= n; ++i) {
      cin >> s;

      M[s] = ++cur;
      calc(i);
    }

    build();

    while(q--) {
      string a, b;
      cin >> a >> b;

      int l = M[a];
      int r = M[b];

      if(l > r)
	swap(l, r);

      printf("%d\n", query(l, r));
    }
  }

  return 0;
}
