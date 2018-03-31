#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;
const int maxn = 3e4 + 10;

int n, t, a[maxn];

vector<int> pos, neg;
int zero;

ll ans = 0;
void solve() {
    for(int i = 1; i <= n; ++i)
	if(a[i] > 0) pos.push_back(a[i]);
	else if(a[i] < 0) neg.push_back(a[i]);
	else ++zero;
	
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());

    ans = 0;

    for(int i = 1; i <= n; ++i) {
	if(!a[i]) {
	    if(t < 0) ans += n;
	}
	else 
	    if(a[i] > 0) {
		if(t < 0) {
		    ans += zero + (int)pos.size();	
		    int x = upper_bound(neg.begin(), neg.end(), t / a[i] - (t % a[i] != 0)) - neg.begin();
		    ans += (int)neg.size() - x;
		}
		else 
		    if(!t) {
			ans += (int)pos.size();
		    }
		    else
			if(t > 0) {
			    int x = upper_bound(pos.begin(), pos.end(), t / a[i]) - pos.begin();
			    ans += (int)pos.size() - x;
			}
	    }
	    else 
		if(a[i] < 0) {
		    if(t < 0) {
			ans += zero + (int)neg.size();
			int x = lower_bound(pos.begin(), pos.end(), t / a[i] + (t % a[i] != 0)) - pos.begin();
			ans += x;
		    }
		    else 
			if(!t) {
			    ans += (int)neg.size();
			}
			else
			    if(t > 0) {
				int x = lower_bound(neg.begin(), neg.end(), t / a[i]) - neg.begin();
				ans += x;
			    }
		}
    }
}

int main() {
    int test = 0;
    srand(time(NULL));
    while(true) {        
	scanf("%d %d", &n, &t);
	if(!n && !t) break;
	zero = 0;
	neg.clear();
	pos.clear();
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);	
	solve();
	ll ways = 1LL * n * n;
	ll gcd = __gcd(ans, ways);
	ans /= gcd;
	ways /= gcd;
	printf("Case %d: %lld/%lld\n", ++test, ans, ways);
    }
    return 0;
}
