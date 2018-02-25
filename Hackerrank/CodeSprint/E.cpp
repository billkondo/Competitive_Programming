#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e6 + 10;

int n, q;
int t[maxn];

struct node {
    int sum;
    int L, R;
} seg[30 * maxn];

int cur;
int root[maxn];

int build(int i, int j) {
    int id = ++cur;
    if(i != j) {
	int mid = (i + j) >> 1;
	seg[id].L = build(i, mid);
	seg[id].R = build(mid + 1, j);
    }
    return id;
}

int update(int idx, int i, int j, int pos, int add) {
    int id = ++cur;
    seg[id].sum = seg[idx].sum;
    seg[id].L = seg[idx].L;
    seg[id].R = seg[idx].R;

    if(i == j) {
	seg[id].sum += add;
	return id;
    }

    int mid = (i + j) >> 1;
    if(pos <= mid) seg[id].L = update(seg[id].L, i, mid, pos, add);
    else seg[id].R = update(seg[id].R, mid + 1, j, pos, add);

    seg[id].sum = seg[seg[id].L].sum + seg[seg[id].R].sum;
    return id;
}

int query(int idx, int i, int j, int l, int r) {
    if(i > j || j < l || r < i || l > r) return 0;
    if(l <= i && j <= r) return seg[idx].sum;
    int mid = (i + j) >> 1;
    return query(seg[idx].L, i, mid, l, r) + query(seg[idx].R, mid + 1, j, l, r);
}

void precompute() {
    root[0] = build(1, n);
    map<int, int> Last, after;
    for(int i = 1; i <= n; ++i) {
	root[i] = root[i - 1];
	if(Last.find(t[i]) == Last.end()) 
	    root[i] = update(root[i], 1, n, i, +1);
	else
	    if(after.find(t[i]) == after.end()) {
		root[i] = update(root[i], 1, n, Last[t[i]], -2);
		root[i] = update(root[i], 1, n, i, +1);
	    }
	    else {
		root[i] = update(root[i], 1, n, after[t[i]], +1);
		root[i] = update(root[i], 1, n, Last[t[i]], -2);
		root[i] = update(root[i], 1, n, i, +1);
	    }

	if(Last.find(t[i]) != Last.end()) after[t[i]] = Last[t[i]];
	Last[t[i]] = i;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &t[i]);
    precompute();
    scanf("%d", &q);
    while(q--) {
	int l, r;
	scanf("%d %d", &l, &r);
	printf("%d\n", query(root[r], 1, n, l, r));
    }
    return 0;
}
