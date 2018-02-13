#include "bits/stdc++.h"
using namespace std;

const int maxn = 20;
const int MAXF = 1e2 + 10;
const int mod = 1e9 + 7;

int T;

int n, x;
long long F[maxn][10];
long long inv[MAXF];

inline long long fastpow(long long a, int b) {
  if(!b)
    return 1LL;

  if(b == 1)
    return a;

  if(b % 2)
    return (a * fastpow(a, b - 1)) % mod;

  long long ret = fastpow(a, b / 2);
  return (ret * ret) % mod;
}

unordered_map <int, long long> ways;
long long prod;
long long resp;

inline void solve(int i, int j) {
  if(j > 6) 
    return;
  
  if(i > (n / 2)) {
    ++ways[prod];
    return;
  }

  prod = (prod * F[i][j]) % mod;
  solve(i + 1, 1);
  prod = (prod * inv[F[i][j]]) % mod;

  solve(i, j + 1);
}

inline void get(int i, int j) {
  if(j > 6)
    return;

  if(i > n) {
    resp += ways[(fastpow(prod, mod - 2) * x) % mod];
    return;
  }

  prod = (prod * F[i][j]) % mod;
  get(i + 1, 1);
  prod = (prod * inv[F[i][j]]) % mod;

  get(i, j + 1);
}

inline long long solve() {
  if(n == 1) {
    int ans = 0;
    
    for(int j = 1; j <= 6; ++j)
      ans += (F[1][j] == x);

    return ans;
  }

  ways.clear();

  prod = 1LL;
  solve(1, 1);

  resp = 0;
  prod = 1LL;
  get((n / 2) + 1, 1);

  return resp;
}

void compute() {
  for(int i = 1; i < MAXF; ++i)
    inv[i] = fastpow(i, mod - 2);
}

int main() {
  scanf("%d", &T);

  compute();
  
  while(T--) {
    scanf("%d %d", &n, &x);

    for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= 6; ++j)
	scanf("%lld", &F[i][j]);

    printf("%lld\n", solve());
  }

  return 0;
}
