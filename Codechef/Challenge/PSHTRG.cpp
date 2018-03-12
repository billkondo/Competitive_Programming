#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 1e5 + 10;
const int LOG = 60;

int n, q;
int a[maxn];

pii seg[4 * maxn];

void build(int idx, int i, int j) {
    if(i == j) {
	seg[idx] = {a[i], i};
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    build(left, i, mid);
    build(right, mid + 1, j);
    seg[idx] = max(seg[left], seg[right]);
}

void update(int idx, int i, int j, int pos) {
    if(i == j) {
	seg[idx] = {a[pos], pos};
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    if(pos <= mid) update(left, i, mid, pos);
    else update(right, mid + 1, j, pos);
    seg[idx] = max(seg[left], seg[right]);
}

pii query(int idx, int i, int j, int l, int r) {
    if(i > j || j < l || r < i) return {0, 0};
    if(l <= i && j <= r) return seg[idx];
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    return max(query(left, i, mid, l, r), query(right, mid + 1, j, l, r));
}

void make(vector<pii> &vec) {
    for(auto p: vec) {
	ll y = p.first;
	int x = p.second;
	a[x] = y;
	update(1, 1, n, x);
    }
}

void find(int l, int r, vector<pii> &values, int &sz) {
    pii k = query(1, 1, n, l, r);
    int x = k.second;
    a[x] = 0;
    ++sz;
    values.push_back(k);
    update(1, 1, n, x);
}

ll get(int l, int r) {
    if(r - l <= 1) return 0LL;

    int sz = 0;
    vector<pii> values;

    find(l, r, values, sz);
    find(l, r, values, sz);

    int cnt = min(LOG, r - l - 1);
    while(cnt) {
	--cnt;

	find(l, r, values, sz);

	if(values[sz - 3].first < values[sz - 2].first + values[sz - 1].first) {
	    ll sum = values[sz - 3].first + values[sz - 2].first + values[sz - 1].first;
	    make(values);
	    return sum;
	}
    }

    make(values);
    return 0LL;
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    build(1, 1, n);
    while(q--) {
	int type, x, y;
	scanf("%d %d %d", &type, &x, &y);
	if(type == 1) {
	    a[x] = y;
	    update(1, 1, n, x);
	}
	else printf("%lld\n", get(x, y));
    }
    return 0;
}
