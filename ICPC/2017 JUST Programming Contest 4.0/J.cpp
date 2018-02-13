#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1e5 + 10;
const long long mod = 1e9 + 7;

int T;

int n;
long long a[MAXN];

long long pre[MAXN];

long long solve() {
  long long ans = 0;
  for(int i = 1; i <= n; ++i) {
    pre[i] = (pre[i - 1] + (pre[i - 1] * a[i])) % mod;
    pre[i] = (pre[i] + a[i]) % mod;

    ans = (ans + (pre[i - 1] + 1) * a[i]) % mod;
  }

  return ans;
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]);

    printf("%lld\n", solve());
  }

  return 0;
}
