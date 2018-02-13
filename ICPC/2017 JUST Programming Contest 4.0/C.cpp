#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;

int T;

int n, a[MAXN];

int ans[MAXN];

multiset <int> Set;

int Max() {
  return *(--Set.end());
}

int get(int D) {
  multiset <int> :: iterator it;

  it = Set.upper_bound(D);

  if(it == Set.begin())
    return -1;

  --it;
  return *it;
}

void solve() {  
  Set.clear();
  for(int i = 1; i <= n; ++i) {
    Set.insert(a[i]);
    ans[i] = -1;
  }

  for(int i = 1; i <= n; ++i) {
    Set.erase(Set.find(a[i]));

    ans[i] = (a[i] + Max()) % mod;
    
    int D = mod - 1 - a[i];

    int x = get(D);

    if(x != -1) 
      ans[i] = max(ans[i], (a[i] + x) % mod);
    
    Set.insert(a[i]);
  }
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);

    solve();

    for(int i = 1; i <= n; ++i)
      printf("%d ", ans[i]);

    printf("\n");
  }
  
  return 0;
}
