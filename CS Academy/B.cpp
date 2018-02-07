#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;

struct point {
    int x, y, id;
};

vector<point> P;

inline bool operator < (point a, point b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x > 0;
}

int n;
int ans[maxn];

int bit[maxn];

void add(int idx, int val) {
    while(idx < maxn) {
	bit[idx] += val;
	idx += (idx & -idx);
    }
}

int get(int idx) {
    int ret = 0;
    while(idx > 0) {
	ret += bit[idx];
	idx -= (idx & -idx);
    }
    return ret;
}

void solve() {
    sort(P.begin(), P.end());
    for(int i = 0; i < n; ++i) {
	int x = P[i].x;
	int id = P[i].id;
	ans[id] = get(x);
	add(x, +1);
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) {
	int x, y;
	cin >> x >> y;
	P.push_back({x, y, i});
    }
    solve();
    for(int i = 0; i < n; ++i) printf("%d\n", ans[i]);
    return 0;
}
