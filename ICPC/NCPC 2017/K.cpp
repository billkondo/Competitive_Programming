#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;

int N;
int cnt[3];
int cur[3];
ll cost[3];
ll c[maxn];

struct Pair {
    ll sum;
    int x, y;
};

vector<Pair> P;

bool ok(ll ans) {
    for(int i = 0; i < 3; ++i) cur[i] = cnt[i];
    for(int i = 1; i <= N; ++i) {
	ll sum = ans / c[i] + (ans % c[i] != 0);
	bool ok = false;
	for(int k = 0; k < 6; ++k) 
	    if(P[k].sum >= sum && ((P[k].x != P[k].y && cur[P[k].x] > 0 && cur[P[k].y] > 0) || (P[k].x == P[k].y && cur[P[k].x] - 2 >= 0))) {
		ok = true;
		--cur[P[k].x];
		--cur[P[k].y];
		break;
	    }
	if(!ok) return false;
    }

    return true;
}

ll solve() {
    ll l = 1;
    ll r = (ll)1e15;

    sort(c + 1, c + 1 + N);

    for(int i = 0; i < 3; ++i)
	for(int j = i; j < 3; ++j) 
	    P.push_back({cost[i] + cost[j], i, j});

    while(l < r) {
	ll mid = (l + r + 1) >> 1;
	if(ok(mid)) l = mid;
	else r = mid - 1;
    }

    return r;
}

int main() {
    cin.sync_with_stdio(false);
    for(int i = 0; i < 3; ++i) {
	cin >> cnt[i];
	N += cnt[i];
    }
    for(int i = 0; i < 3; ++i) cin >> cost[i];
    N /= 2;
    for(int i = 1; i <= N; ++i) cin >> c[i];
    cout << solve() << endl;
    return 0;
}
