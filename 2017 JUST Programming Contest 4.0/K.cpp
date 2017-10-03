#include "bits/stdc++.h"
using namespace std;

const int MAXN = 30;

int T;

int n;
char s[MAXN];

map <char, int> M;

long long fat[MAXN];

long long solve() {
  int odd = 0;

  int total = 0;
  
  for(char c = 'a'; c <= 'z'; ++c) {
    if(M[c] % 2) {
      ++odd;
      --M[c];
    }

    M[c] /= 2;

    total += M[c];
  }

  if(odd > 1)
    return 0LL;

  long long ans = fat[total];

  for(char c = 'a'; c <= 'z'; ++c)
    ans /= fat[M[c]];
  
  return ans;
}

void compute() {
  fat[0] = 1;
  for(int i = 1; i <= 20; ++i)
    fat[i] = 1LL * fat[i - 1] * i;
}

int main() {
  scanf("%d", &T);

  compute();

  while(T--) {
    scanf("%d %s", &n, s);

    M.clear();

    for(int i = 0; i < n; ++i)
      ++M[s[i]];

    printf("%lld\n", solve());
  }

  return 0;
}
