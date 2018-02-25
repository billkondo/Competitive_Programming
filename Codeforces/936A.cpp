#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

ll k, d, t;

ll P;

bool ok(long double T) {
    ll Time = floor(T);
    ll cnt = Time / P;

    long double cur = 0;
    
    cur += k * cnt;
    cur += 1.0 * (P - k) * cnt / 2.0;
    
    T -= cnt * P;
    
    if(T >= k) cur += k, T -= k;
    else cur += T, T = 0;
    
    if(T) cur += 1.0 * T / 2.0;
    
    return cur >= t;
}

long double solve() {
    long double l = 0.0;
    long double r = 2e18;
    
    ll rep;
    
    rep = (k / d) + (k % d != 0);
    P = rep * d;

    for(int it = 0; it <= 1000; ++it) {
    	long double mid = (l + r) / 2.0;
    	if(ok(mid)) r = mid;
    	else l = mid;
    }

    return r;
}

int main() {
    cin.sync_with_stdio(false);
    cin >> k >> d >> t;
    cout << fixed << setprecision(15) << solve() << '\n';
    return 0;
}
