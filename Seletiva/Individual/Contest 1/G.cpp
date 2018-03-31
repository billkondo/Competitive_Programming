#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

const int maxn = 1e4 + 10;
const int maxm = 1e2 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int c[maxn], p[maxn], jump[maxn];

vector<int> pos;

int dp[maxm][maxn];
int pre[maxn];

int getSum(int l, int r) {
    if(l > r) return 0;
    if(!l) return pre[r];
    return pre[r] - pre[l - 1];
}

struct line {
    int cost;
    int r;
};

vector<line> Line[maxn];

void getIntervals() {
    for(int i = 0; i < n; ++i) Line[i].clear();
    for(int i = 0; i < n; ++i) {
	int l = lower_bound(pos.begin(), pos.end(), pos[i] - jump[i]) - pos.begin();
	int r = --upper_bound(pos.begin(), pos.end(), pos[i] + jump[i]) - pos.begin();
	Line[l].push_back({c[i], r});
    }
}

struct node {
    int MinIn, MinOut;
    void merge(node L, node R) {
	MinIn = min(L.MinIn, R.MinIn);
	MinOut = min(L.MinOut, R.MinOut);
    }
} seg[4 * maxn];

void build(int idx, int i, int j, int M) {
    if(i == j) {
	seg[idx].MinOut = dp[M][i];
	int add = i ? pre[i - 1] : 0;
	seg[idx].MinIn = dp[M][i] - add;
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;

    build(left, i, mid, M);
    build(right, mid + 1, j, M);
    
    seg[idx].merge(seg[left], seg[right]);
}

int query(int idx, int i, int j, int l, int r, int type) {
    if(i > j || j < l || r < i) return INF;
    if(l <= i && j <= r) return type ? seg[idx].MinOut : seg[idx].MinIn;
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    return min(query(left, i, mid, l, r, type), query(right, mid + 1, j, l, r, type));
}

int solve() {
    getIntervals();
    pre[0] = p[0];
    for(int i = 1; i < n; ++i) pre[i] = pre[i - 1] + p[i];

    int ans = pre[n - 1];
    for(int l = 0; l < n; ++l) {
	int add = l ? pre[l - 1] : 0;
	dp[0][l] = INF;
	for(auto k: Line[l]) {
	    int cost = k.cost;
	    int r = k.r;
	    dp[0][l] = min(dp[0][l], cost + add + getSum(r + 1, n - 1));
	}
	ans = min(ans, dp[0][l]);
    }

    for(int j = 1; j <= m - 1; ++j) {
	build(1, 0, n - 1, j - 1);
	for(int l = n - 1; l >= 0; --l) {
	    int add = l ? pre[l - 1] : 0;
	    dp[j][l] = INF;
	    for(auto k: Line[l]) {
		int cost = k.cost;
		int r = k.r;
		dp[j][l] = min(dp[j][l], add + cost + query(1, 0, n - 1, l, r, 0));		
		if(r + 1 <= n - 1) dp[j][l] = min(dp[j][l], add + cost + query(1, 0, n - 1, r + 1, n - 1, 1) - pre[r]);
		dp[j][l] = min(dp[j][l], add + cost + getSum(r + 1, n - 1));
	    }
	    ans = min(ans, dp[j][l]);
	}
    }
    
    return ans;
}

int main() {
    int test = 0;
    while(true) {
	scanf("%d %d", &n, &m);
	if(!n && !m) break;
	pos.clear();
	pos.push_back(0);
	for(int i = 1; i <= n - 1; ++i) {
	    int d;
	    scanf("%d", &d);
	    pos.push_back(d);
	}
	for(int i = 0; i < n; ++i) scanf("%d", &c[i]);
	for(int i = 0; i < n; ++i) scanf("%d", &jump[i]);
	for(int i = 0; i < n; ++i) scanf("%d", &p[i]);
	printf("Case %d: %d\n", ++test, solve());
    }
    return 0;
}
