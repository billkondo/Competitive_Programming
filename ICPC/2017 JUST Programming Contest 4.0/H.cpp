#include "bits/stdc++.h"
using namespace std;

const int MAXN = 60;

int T;

int n, m;
char s[MAXN][MAXN];

int solve() {
  int Zeros = 0, Ones = 0;

  for(int i = 1; i <= n; ++i) 
    Zeros += (s[i][1] == '0') + (s[i][m] == '0');
 
  for(int j = 2; j < m; ++j)
    Zeros += (s[1][j] == '0') + (s[n][j] == '0');

  for(int i = 2; i <= n - 1; ++i)
    for(int j = 2; j <= m - 1; ++j)
      if(s[i][j] == '1')
	++Ones;
  
  if(Zeros > Ones)
    return -1;

  return Zeros;
}

int main() {
  scanf("%d", &T);

  while(T--) {
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= m; ++j)
	scanf(" %c", &s[i][j]);

    printf("%d\n", solve());
  }

  return 0;
}
