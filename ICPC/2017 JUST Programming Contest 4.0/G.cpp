#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1e6 + 10;

int T, n, a[MAXN];

int pre[MAXN];
int suf[MAXN];

int solve() {
  int ans = 0;

  pre[1] = a[1];

  for(int i = 2; i <= n; ++i) 
    pre[i] = max(pre[i - 1], a[i]);

  suf[n] = a[n];

  for(int i = n - 1; i >= 1; --i)
    suf[i] = min(suf[i + 1], a[i]);

  for(int i = 2; i < n; ++i) 
    if(pre[i] == a[i] && suf[i] == a[i]) 
      ++ans;

  return ans;
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);

    printf("%d\n", solve());
  }

  return 0;
}
