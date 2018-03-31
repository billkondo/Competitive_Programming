#include "bits/stdc++.h"
using namespace std;

#define debug(args...) //fprintf(stderr, args);

typedef long long ll;

const ll mod = 1e9 + 7;

int t, n, r, k;
ll a[30];

int len;

struct matrix {
    ll m[30][30];
    matrix() { memset(m, 0, sizeof(m)); }
};

matrix mult(matrix a, matrix b) {
    matrix c;
    for(int i = 1; i <= len; ++i)
	for(int j = 1; j <= len; ++j)
	    for(int k = 1; k <= len; ++k)
		c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return c;
}

matrix fpow(matrix a, int b) {
    if(b == 1) return a;
    if(b & 1) return mult(a, fpow(a, b - 1));
    matrix c = fpow(a, b / 2);
    return mult(c, c);
}

ll s[30];

ll solve() {
    int c = 1;
    while(r > c * k) ++c;

    for(int i = r + 1; i <= k * c; ++i) {
	s[i] = 0;
	for(int j = 1; j <= r; ++j)
	    s[i] = (s[i] + a[j] * s[i - j]) % mod;
    }
    
    ll ans = 0;

    int K = c * k;

    debug("c = %d\n", c);

    if(n <= c) {
	for(int i = 1, j = k; i <= n; ++i, j += k)
	    ans = (ans + s[j]) % mod;

	return ans;
    }

    debug("exponentiation\n");

    len = K;

    matrix by_one;

    for(int i = 1; i <= r; ++i)
	by_one.m[len][len - i + 1] = a[i];
    
    int x = len - 1;
    int y = len;
    while(x >= 1 && y >= 1) {
	by_one.m[x][y] = 1;
	--x;
	--y;
    }
    
    debug("by_one\n");
    for(int i = 1; i <= len; ++i) {
	for(int j = 1; j <= len; ++j)
	    debug("%lld ", by_one.m[i][j]);
	debug("\n");
    }

    matrix t;
    t = fpow(by_one, k);

    debug("t:\n");
    for(int i = 1; i <= len; ++i) {
	for(int j = 1; j <= len; ++j)
	    debug("%lld ", t.m[i][j]);
	debug("\n");
    }

    len = K + 1;
    matrix T;

    for(int i = 1; i <= len; ++i)
	for(int j = 1; j <= len; ++j)
	    T.m[i][j] = t.m[i][j];

    for(int j = 1; j <= len; ++j)
	T.m[len][j] = t.m[len - 1][j];

    T.m[len][len] = 1;

    debug("T:\n");
    for(int i = 1; i <= len; ++i) {
	for(int j = 1; j <= len; ++j)
	    debug("%lld ", T.m[i][j]);
	debug("\n");
    }

    s[len] = 0;
    for(int i = 1, j = k; i <= c; ++i, j += k)
	s[len] = (s[len] + s[j]) % mod;

    matrix base = fpow(T, n - c);

    for(int j = 1; j <= len; ++j)
	ans = (ans + base.m[len][j] * s[j]) % mod;
	
    return ans;
}

int main() {
    scanf("%d", &t);
    while(t--) {
	scanf("%d %d %d", &n, &r, &k);
	for(int i = 1; i <= r; ++i) scanf("%lld", &s[i]);
	for(int i = 1; i <= r; ++i) scanf("%lld", &a[i]);
	printf("%lld\n", solve());
    }
    return 0;
}
