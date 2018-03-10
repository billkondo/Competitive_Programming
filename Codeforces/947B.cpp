#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 1e5 + 10;
const ll INF = 1e18;

int n, v[maxn], t[maxn];

struct node {
    pii T;
    ll lazy;
    int sz;

    void merge(node L, node R) {
	T = min(L.T, R.T);
	sz = L.sz + R.sz;
    }
} seg[4 * maxn];

void build(int idx, int i, int j) {
    if(i == j) {
	seg[idx].T = {v[i], i};
	seg[idx].sz = 1;
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    build(left, i, mid);
    build(right, mid + 1, j);
    seg[idx].merge(seg[left], seg[right]);
}

void refresh(int idx, int i, int j) {
    if(!seg[idx].lazy) return;
    ll add = seg[idx].lazy;
    if(i != j) {
	int left = idx << 1;
	int right = left | 1;
	if(seg[left].T.first != INF) seg[left].lazy += add;
	if(seg[right].T.first != INF) seg[right].lazy += add;
    }
    seg[idx].T.first -= add;
    seg[idx].lazy = 0;
}

void update(int idx, int i, int j, int l, int r, ll val) {
    refresh(idx, i, j);
    if(i > j || j < l || r < i || seg[idx].T.first == INF) return;
    if(l <= i && j <= r) {
	seg[idx].lazy += val;
	refresh(idx, i, j);
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    update(left, i, mid, l, r, val);
    update(right, mid + 1, j, l, r, val);
    seg[idx].merge(seg[left], seg[right]);
}

void rem(int idx, int i, int j, int pos) {
    refresh(idx, i, j);
    if(i == j) {
	seg[idx].T = {INF, 0};
	seg[idx].sz = 0;
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    refresh(left, i, mid);
    refresh(right, mid + 1, j);
    if(pos <= mid) rem(left, i, mid, pos);
    else rem(right, mid + 1, j, pos);
    seg[idx].merge(seg[left], seg[right]);
}

pii query(int idx, int i, int j, int l, int r) {
    refresh(idx, i, j);
    if(i > j || j < l || r < i) return {INF, 0};
    if(l <= i && j <= r) return seg[idx].T;
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    return min(query(left, i, mid, l, r), query(right, mid + 1, j, l, r));
}

int get(int idx, int i, int j, int l, int r) {
    refresh(idx, i, j);
    if(i > j || j < l || r < i) return 0;
    if(l <= i && j <= r) return seg[idx].sz;
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    return get(left, i, mid, l, r) + get(right, mid + 1, j, l, r);
}

void solve() {
    build(1, 1, n);
    for(int i = 1; i <= n; ++i) {	
    	pii q = query(1, 1, n, 1, i);
    	ll ans = 0;

    	while(q.first < t[i]) {
    	    ans += q.first;
    	    rem(1, 1, n, q.second);
    	    q = query(1, 1, n, 1, i);
    	}

    	ans += 1LL * t[i] * get(1, 1, n, 1, i);
    	update(1, 1, n, 1, i, t[i]);
    	printf("%lld ", ans);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &v[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &t[i]);
    solve();
    return 0;
}
