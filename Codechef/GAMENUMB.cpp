#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5 + 10;

int t;

int n, k;
int a[maxn];
int d[maxn];
ll b[maxn];

ll bit[maxn];

void add(int idx, ll val) {
    while(idx <= n) {
	bit[idx] += val;
	idx += (idx & -idx);
    }
}

ll query(int idx) {
    ll sum = 0;
    while(idx > 0) {
	sum += bit[idx];
	idx -= (idx & -idx);
    }
    return sum;
}

ll solve() {
    for(int i = 1; i <= n; ++i) bit[i] = 0;
    vector<pii> cards;
    
    for(int i = 1; i <= n; ++i) cards.push_back({a[i], d[i]});
    sort(cards.begin(), cards.end());

    int l = 1;
    int r = n;


    for(int i = 1; i <= n; ++i) {
	a[i] = cards[i - 1].first;
	d[i] = cards[i - 1].second;
	add(i, d[i]);
    }

    for(int i = 1; i <= k; ++i)	
	if(i % 2) {
	    int L = l;
	    int R = r;

	    while(L < R) {
		int mid = (L + R) >> 1;
		ll sum = query(R) - query(mid - 1);

		if(sum <= b[i]) R = mid - 1;
		else L = mid;
	    }

	    l = R + 1;
	    ll sum = query(r) - query(l - 1);

	    add(l, -sum + b[i]);
	}
	else {
	    int L = l;
	    int R = r;

	    while(L < R) {
		int mid = (L + R) >> 1;
		ll sum = query(mid) - query(l - 1);

		if(sum >= b[i]) L = mid + 1;
		else R = mid;
	    }

	    r = L - 1;
	    ll sum = query(r) - query(l - 1);
	    add(r, -sum + b[i]);
	}
    
    ll sum = 0;
    for(int i = l; i <= r; ++i) sum += 1LL * (query(i) - query(i - 1)) * a[i];

    return sum;
}

int main() {
    scanf("%d", &t);
    while(t--) {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &d[i]);
	for(int i = 1; i <= k; ++i) scanf("%lld", &b[i]);
	printf("%lld\n", solve());
    }
}
