#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef pair<int, int> pii;

const int maxn = 2e5 + 10;

int n;
vector<pii> adj[2][maxn];
pii e[2 * maxn];
bool mrk[2 * maxn];
int IDX;

int st[2][maxn], ed[2][maxn], cur[2];
vector<pii> E[2][maxn];

struct point {
    int x, y, id;

    point() { x = y = id = 0; }
    point(int x, int y, int id) : x(x), y(y), id(id) {}
};

inline bool operator < (point a, point b) { return a.x < b.x; };
inline point min (point a, point b) { return a < b ? a : b; }
inline point max (point a, point b) { return a < b ? b : a; }

struct node {
    vector<point> MAX, MIN;
    point Max, Min;

    void merge(node L, node R) {
	Max = max(L.Max, R.Max);
	Min = min(L.Min, R.Min);
    }
} seg[2][4 * maxn];

void build(int k, int idx, int i, int j) {
    if(i == j) {
	sort(E[k][i].begin(), E[k][i].end());

	for(auto p: E[k][i]) {
	    int val = p.first;
	    int id = p.second;

	    seg[k][idx].MAX.push_back({val, i, id});
	    seg[k][idx].MIN.push_back({val, i, id});
	}

	reverse(seg[k][idx].MIN.begin(), seg[k][idx].MIN.end());

	if(!seg[k][idx].MAX.empty()) seg[k][idx].Max = seg[k][idx].MAX.back();
	else seg[k][idx].Max = {0, 0, 0};

	if(!seg[k][idx].MIN.empty()) seg[k][idx].Min = seg[k][idx].MIN.back();
	else seg[k][idx].Min = {n + 1, 0, 0};

	return;
    }

    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    build(k, left, i, mid);
    build(k, right, mid + 1, j);

    seg[k][idx].merge(seg[k][left], seg[k][right]);
}

void update(int k, int idx, int i, int j, int pos, int type) {
    if(i == j) {
	if(!type) {
	    seg[k][idx].MAX.pop_back();

	    if(!seg[k][idx].MAX.empty()) seg[k][idx].Max = seg[k][idx].MAX.back();
	    else seg[k][idx].Max = {0, 0, 0};
	}
	else {
	    seg[k][idx].MIN.pop_back();

	    if(!seg[k][idx].MIN.empty()) seg[k][idx].Min = seg[k][idx].MIN.back();
	    else seg[k][idx].Min = {n + 1, 0, 0};
	}

	return;
    }

    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    if(pos <= mid) update(k, left, i, mid, pos, type);
    else update(k, right, mid + 1, j, pos, type);

    seg[k][idx].merge(seg[k][left], seg[k][right]);
}

point query(int k, int idx, int i, int j, int l, int r, int type) {
    if(i > j || j < l || r < i || l > r) return !type ? point(0, 0, 0) : point(n + 1, 0, 0);
    if(l <= i && j <= r) return !type ? seg[k][idx].Max : seg[k][idx].Min;

    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    point L = query(k, left, i, mid, l, r, type);
    point R = query(k, right, mid + 1, j, l, r, type);

    return !type ? max(L, R) : min(L, R);
}

void dfs(int k, int v, int par) {
    st[k][v] = ++cur[k];
   
    for(auto i: adj[k][v]) {
	int u = i.first;
	int id = i.second;

	if(u == par) continue;

	dfs(k, u, v);
    }
    
    ed[k][v] = cur[k];
}

void dfsBuild(int k, int v, int par) {
    for(auto i: adj[k][v]) {
	int u = i.first;
	int id = i.second;

	if(u == par) continue;

	dfsBuild(k, u, v);

	if(!k && id == IDX) continue;

	int L = min(st[k ^ 1][u], st[k ^ 1][v]);
	int R = max(st[k ^ 1][u], st[k ^ 1][v]);

	E[k ^ 1][L].push_back({R, id});
	E[k ^ 1][R].push_back({L, id});
    }
}

void solve() {
    for(int k = 0; k <= 1; ++k) dfs(k, 1, -1);
    for(int k = 0; k <= 1; ++k) dfsBuild(k, 1, -1);
    for(int k = 0; k <= 1; ++k) build(k, 1, 1, n);
    
    vector<int> idx;

    idx.push_back(IDX);
    int k = 0;
    
    while(!idx.empty()) {
	if(!k) printf("Blue\n");
	else printf("Red\n");

	sort(idx.begin(), idx.end());

	vector<int> vec;

	for(auto id: idx) {
	    if(k) printf("%d ", id - (n - 1));
	    else printf("%d ", id);

	    int u = e[id].first;
	    int v = e[id].second;

	    int l = max(st[k][u], st[k][v]);
	    int r = min(ed[k][u], ed[k][v]);
	    
	    for(int type = 0; type <= 1; ++type) {
		point q = query(k, 1, 1, n, l, r, type);

		while((!type && q.x > r) || (type && q.x < l)) {
		    int x = q.x;
		    int y = q.y;
		    int id = q.id;

		    update(k, 1, 1, n, y, type);

		    if(!mrk[id]) vec.push_back(id);

		    mrk[id] = true;

		    q = query(k, 1, 1, n, l, r, type);
		}
	    }
	}

	printf("\n");

	idx.clear();
	for(auto id: vec) idx.push_back(id);
	
	k ^= 1;
    }
}

int main() {
    scanf("%d", &n);

    for(int k = 0; k <= 1; ++k)
	for(int i = 1; i <= n - 1; ++i) {
	    int id = k * (n - 1) + i;
	    int x;
	    int y = i + 1;

	    scanf("%d", &x);

	    adj[k][x].push_back({y, id});
	    adj[k][y].push_back({x, id});
	    e[id] = {x, y};
	}

    scanf("%d", &IDX);

    solve();

    return 0;
}
