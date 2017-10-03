#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1e5 + 10;

int T;

int n, a[MAXN], b[MAXN];

long long get(int k) {
  long long add = (1LL << k);
  long long ans = 0;

  for(int i = 1; i <= n; ++i)
    if((1 << k) & a[i])
      b[i] = 1;
    else
      b[i] = 0;

  for(int i = 1; i <= n; ++i) {
    if(!b[i])
      continue;

    int j = i;
    while(j + 1 <= n && b[j + 1])
      ++j;

    long long len = j - i + 1;

    len = (len) * (len + 1) / 2;

    ans += add * len;

    i = j;
  }
  
  return ans;
}

long long solve() {
  long long ans = 0;

  for(int bit = 0; bit < 30; ++bit)
    ans += get(bit);
  
  return ans;
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);

    printf("%lld\n", solve());
  }
  
  return 0;
}
