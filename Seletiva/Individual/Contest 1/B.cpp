#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 5e4 + 10;

int n, q;

ll x[maxn], y[maxn];

ll cross(int i, int j) { return x[i] * y[j] - y[i] * x[j]; }
ll sum[maxn];

void precompute() {
    sum[0] = 0;
    for(int i = 1; i <= n; ++i)
	sum[i] = sum[i - 1] + cross(i, (i % n) + 1);
}

int main() {
    cin.sync_with_stdio(false);
    int test = 0;
    while(true) {
	cin >> n >> q;
	if(!n && !q) break;
	++test;
	if(test > 1) cout << '\n';
	for(int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
	precompute();
	while(q--) {
	    int a, b;
	    cin >> a >> b;
	    ++a, ++b;
	    ll A = abs(sum[b - 1]  - sum[a - 1] + cross(b, a));	    
	    ll B = abs(sum[n]) - A;	    
	    ll C = min(A, B);
	    if(C % 2 == 0) cout << C / 2LL << ".0\n";
	    else cout << C / 2LL << ".5\n";
	} 
    }
    return 0;
}
