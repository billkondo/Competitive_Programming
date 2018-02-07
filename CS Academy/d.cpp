#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 1e3 + 10;

int n, m;
ll dig[maxn][maxn];
ll rect[maxn][maxn];

void pushDig() {
    for(int i = n; i >= 1; --i) {
	ll sum = 0;
	int R = i;
	int C = 1;

	while(R <= n && C <= n) {
	    sum += dig[R][C];
	    dig[R][C] = sum;
	    ++R;
	    ++C;
	}
    }

    for(int j = 2; j <= n; ++j) {
	ll sum = 0;
	int R = 1;
	int C = j;

	while(R <= n && C <= n) {
	    sum += dig[R][C];
	    dig[R][C] = sum;
	    ++R;
	    ++C;
	}
    }

    for(int j = 1; j <= n; ++j) {
	ll sum = 0;
	for(int i = 1; i <= n; ++i) {
	    sum += dig[i][j];
	    dig[i][j] = sum;
	}
    }
}

void pushRect() {
    for(int i = 1; i <= n; ++i) {
	ll sum = 0;
	for(int j = 1; j <= n; ++j) {
	    sum += rect[i][j];
	    rect[i][j] = sum;
	}
    }

    for(int j = 1; j <= n; ++j) {
	ll sum = 0;
	for(int i = 1; i <= n; ++i) {
	    sum += rect[i][j];
	    rect[i][j] = sum;
	}
    }
}

void solve() {
    pushDig();
    pushRect();
}

int main() {
    scanf("%d %d", &n, &m);
    for(int it = 1; it <= m; ++it) {
	int r, c, l, s;
	scanf("%d %d %d %d", &r, &c, &l, &s);
	int i = min(n, r + l - 1);
	int j = min(n, c + l - 1);
	dig[r][c] += s;
	dig[i + 1][j + 1] -= s;
	rect[i + 1][c] -= s;
	rect[i + 1][j + 1] += s;
    }
    solve();
    for(int i = 1; i <= n; ++i) {
	for(int j = 1; j <= n; ++j)
	    printf("%lld ", rect[i][j] + dig[i][j]);
	printf("\n");
    }
    return 0;
}
