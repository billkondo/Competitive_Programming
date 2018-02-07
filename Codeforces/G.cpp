#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;
const int maxn = 75000 + 10;
const ll mod = 1e9;

int n, q;

struct func {
    ll x1, x2, y1, a, b, y2;
} F[maxn];

int N = 0;
set<ll> X;
map<ll, int> M;

void compress() {
    X.insert(0);
    for(auto i: X) M[i] = ++N;
}

struct node {
    ll sum, A;
    int L, R;
} seg[100 * maxn];

int root[maxn];
int cur;

int build(int i, int j) {
    int id = ++cur;
    if(i != j) {
	int mid = (i + j) >> 1;
	seg[id].L = build(i, mid);
	seg[id].R = build(mid + 1, j);
    }
    return id;
}

int update(int now, int i, int j, int pos, int val, int type) {
    int id = ++cur;
    seg[id].sum = seg[now].sum;
    seg[id].A = seg[now].A;
    seg[id].L = seg[now].L;
    seg[id].R = seg[now].R;
    if(i == j) {
	if(!type) seg[id].sum += val;
	else seg[id].A += val;
	return id;
    }
    int mid = (i + j) >> 1;
    if(pos <= mid) seg[id].L = update(seg[id].L, i, mid, pos, val, type);
    else seg[id].R = update(seg[id].R, mid + 1, j, pos, val, type);
    seg[id].sum = seg[seg[id].L].sum + seg[seg[id].R].sum;
    seg[id].A = seg[seg[id].L].A + seg[seg[id].R].A;
    return id;
}

ll query(int L, int R, int i, int j, int l, int r, int type) {
    if(i > j || j < l || r < i || l > r) return 0;
    if(l <= i && j <= r) return type ? seg[R].A - seg[L].A : seg[R].sum - seg[L].sum;
    int mid = (i + j) >> 1;
    return query(seg[L].L, seg[R].L, i, mid, l, r, type) + query(seg[L].R, seg[R].R, mid + 1, j, l, r, type);
}

void compute() {
    compress();
    root[0] = build(1, N);
    for(int i = 1; i <= n; ++i) {
	root[i] = root[i - 1];
	root[i] = update(root[i], 1, N, M[0], F[i].y1, 0);
	root[i] = update(root[i], 1, N, M[F[i].x1 + 1], F[i].b -F[i].y1, 0);
	root[i] = update(root[i], 1, N, M[F[i].x2 + 1], F[i].y2 - F[i].b, 0);
	root[i] = update(root[i], 1, N, M[F[i].x1 + 1], F[i].a, 1);
	root[i] = update(root[i], 1, N, M[F[i].x2 + 1], -F[i].a, 1);
    }
}

int findId(int x) {
    return M[*(--X.upper_bound(x))];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
	ll x1, x2, y1, a, b, y2;
	scanf("%lld %lld %lld %lld %lld %lld", &x1, &x2, &y1, &a, &b, &y2);
	X.insert(x1);
	X.insert(x1 + 1);
	X.insert(x2);
	X.insert(x2 + 1);
	F[i] = {x1, x2, y1, a, b, y2};
    }
    compute();
    scanf("%d", &q);
    ll last = 0;
    while(q--) {
	int l, r;
	ll x;
	scanf("%d %d %lld", &l, &r, &x);
	x = (x + last) % mod;
	int pos = findId(x);
	ll ans = query(root[l - 1], root[r], 1, N, 1, pos, 0);
	ll a = query(root[l - 1], root[r], 1, N, 1, pos, 1); 
	ans += 1LL * a * x;
	last = ans;
	printf("%lld\n", ans);
    }
    return 0;
}
