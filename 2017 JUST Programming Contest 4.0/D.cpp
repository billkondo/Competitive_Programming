#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

const int MAXN = 1e4 + 10;
const int ALPHA = 30;

int T;

int n, q;
char s[MAXN];

int freq[ALPHA];
int pre[ALPHA][MAXN];

int get(int L, int R, int id) {
  if(L > R)
    return 0;
  
  return pre[id][R] - pre[id][L - 1];
}

void compute() {
  for(int c = 0; c < ALPHA; ++c)
    freq[c] = 0;

  for(int i = 1; i <= n; ++i)
    ++freq[s[i] - 'a'];

  for(int i = 1; i <= n; ++i) {
    for(int c = 0; c < ALPHA; ++c)
      pre[c][i] = pre[c][i - 1];

    ++pre[s[i] - 'a'][i];
  }
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d %d", &n, &q);

    for(int i = 1; i <= n; ++i)
      scanf(" %c", &s[i]);

    compute();

    while(q--) {
      int l, r;
      char c;
      scanf("%d %d %c", &l, &r, &c);

      int id = c - 'a';
      
      int p = (l / n) + (l % n != 0);

      int q = (r / n);

      int ans = 0;

      if(p <= q) {
	ans += (q - p) * freq[id];
	ans += get(n - (p * n - l + 1) + 1, n, id);
	ans += get(1, r - q * n, id);
      }
      else {
	int L = (l % n);
	int R = (r % n);

	if(!L)
	  L = n;

	if(!R)
	  R = n;
	
	ans = get(L, R, id);
      }
      
      printf("%d\n", ans);
    }
  }

  return 0;
}
