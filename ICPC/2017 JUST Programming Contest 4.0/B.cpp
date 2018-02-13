#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1e3 + 10;

int T, n, m, a[MAXN];

int b[MAXN];

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);

    int idx = -1;

    for(int i = 1; i <= n; ++i)
      if(a[i] != -1) {
	idx = i;
	break;
      }

    b[idx] = a[idx];
    for(int i = idx + 1; i <= n; ++i)
      b[i] = (b[i - 1] + 1) % m;

    for(int i = idx - 1; i >= 1; --i)
      b[i] = (b[i + 1] - 1 + m) % m;
      
    for(int i = 1; i <= n; ++i)
      printf("%d ", b[i]);

    printf("\n");
  }

  return 0;
}
